#include <Wire.h>
#include <LiquidCrystal.h> 

const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Hardware I2C bus addresses for the two MPU-6050 chips
const int MPU1_ADDR = 0x68; // Address for Upper Back sensor (AD0 wired to GND)
const int MPU2_ADDR = 0x69; // Address for Lower Back sensor (AD0 wired to 3.3V)

// Storage variables for the baseline "good posture" angles
float upperBaseline = 0.0;  // Holds upper back target angle after calibration
float lowerBaseline = 0.0;  // Holds lower back target angle after calibration
bool isCalibrated = false;  // Verification flag to track if countdown finished

const float UPPER_WARN_THRESHOLD = 20.0; // Angle drift required for Medium status
const float UPPER_BAD_THRESHOLD  = 30.0; // Angle drift required for Bad status

const float LOWER_WARN_THRESHOLD = 10.0;  // Angle drift required for Medium status
const float LOWER_BAD_THRESHOLD  = 15.0; // Angle drift required for Bad status

void setup() {
  Serial.begin(115200);     // Open serial data port at 115200 baud rate for logging
  Wire.begin();             // Wake up internal Arduino I2C communication engine
  
  lcd.begin(16, 2);         // Establish LCD grid size at 16 columns and 2 rows
  lcd.clear();              // Wipe screen memory clear of any initial artifacts
  
  initMPU(MPU1_ADDR);       // Power on and un-sleep the upper back sensor chip
  initMPU(MPU2_ADDR);       // Power on and un-sleep the lower back sensor chip
  
  //Countdown Sequence
  for (int i = 5; i > 0; i--) { // i = 5; i-- mean i decrease after 1 loop which indicate 5 loop
    lcd.setCursor(0, 0);        // column 0, row 0(top line)
    lcd.print("Sit Straight!   ");
    lcd.setCursor(0, 1);        // column 0, row 1 (bottom line)
    lcd.print("Calibrating: " + String(i) + "  "); // Print number countdown
    delay(1000);                // 1 sec delay
  }
  
  // Lock in baseline angles at the exact moment the countdown ends
  upperBaseline = getPitch(MPU1_ADDR); // Capture frozen upper target alignment angle
  lowerBaseline = getPitch(MPU2_ADDR); // Capture frozen lower target alignment angle
  isCalibrated = true;                 // Set tracking system validation flag to active
  
  lcd.setCursor(0, 0);          // Jump cursor to top line column 0
  lcd.print("Calibrated!     "); // Display successful calibration message
  lcd.setCursor(0, 1);          // Jump cursor to bottom line column 0
  lcd.print("Tracking Active "); // Inform user the sensors are evaluating posture
  delay(1500);                  // Leave status text on screen for 1.5 seconds
  lcd.clear();                  // Clear the display grid for normal operation mode
}

void loop() {
  // 1. Grab fresh, real-time raw pitch angles from both data sensors
  float currentUpperPitch = getPitch(MPU1_ADDR); // Read live upper back sensor angle
  float currentLowerPitch = getPitch(MPU2_ADDR); // Read live lower back sensor angle
  
  // 2. Compute absolute deviation degrees by comparing live angles to baseline targets
  float upperDeviation = abs(currentUpperPitch - upperBaseline); // Calculate upper shift
  float lowerDeviation = abs(currentLowerPitch - lowerBaseline); // Calculate lower shift
  
  //Real time output show in Serial monitor
  Serial.print("Upper_Raw: "); Serial.print(currentUpperPitch);
  Serial.print(" | Upper_Dev: "); Serial.print(upperDeviation);
  Serial.print(" || Lower_Raw: "); Serial.print(currentLowerPitch);
  Serial.print(" | Lower_Dev: "); Serial.println(lowerDeviation);
  
  // 3. Evaluate Upper Back alignment parameters against safety cutoffs
  String upperStatus = "Good  "; // Establish "Good" status as default baseline state
  if (upperDeviation >= UPPER_BAD_THRESHOLD) { // Check if upper drift crossed 15 degrees
    upperStatus = "Bad   ";                   // Shift status string to Bad description
  } else if (upperDeviation >= UPPER_WARN_THRESHOLD) { // Check if upper drift crossed 10
    upperStatus = "Medium";                           // Shift status string to Medium
  }

  // 4. Evaluate Lower Back alignment parameters against safety cutoffs
  String lowerStatus = "Good  "; // Establish "Good" status as default baseline state
  if (lowerDeviation >= LOWER_BAD_THRESHOLD) { // Check if lower drift crossed 12 degrees
    lowerStatus = "Bad   ";                   // Shift status string to Bad description
  } else if (lowerDeviation >= LOWER_WARN_THRESHOLD) { // Check if lower drift crossed 8
    lowerStatus = "Medium";                           // Shift status string to Medium
  }
  
  // --- COMPILATION AND REFRESH OF 16x2 PARALLEL LCD DISPLAY INTERFACE ---
  
  // Row 1 Setup: Upper back text parameters
  lcd.setCursor(0, 0);          // Focus writing cursor at top line column 0
  lcd.print("U:");               // Prefix tag for Upper Back data identifier
  lcd.print(upperDeviation, 1); // Render current upper offset limited to 1 decimal place
  lcd.print((char)223);         // Write special system character map code for degree symbol (°)
  lcd.print("   ");             // Print blank string clear spaces to block out digit artifacts
  
  lcd.setCursor(10, 0);         // Snap cursor directly to structural column index 10
  lcd.print(upperStatus);       // Print matching 6-character evaluation status word
  
  // Row 2 Setup: Lower back text parameters
  lcd.setCursor(0, 1);          // Focus writing cursor at bottom line column 0
  lcd.print("L:");               // Prefix tag for Lower Back data identifier
  lcd.print(lowerDeviation, 1); // Render current lower offset limited to 1 decimal place
  lcd.print((char)223);         // Write special system character map code for degree symbol (°)
  lcd.print("   ");             // Print blank string clear spaces to block out digit artifacts
  
  lcd.setCursor(10, 1);         // Snap cursor directly to structural column index 10
  lcd.print(lowerStatus);       // Print matching 6-character evaluation status word
  
  delay(500); // Wait 500ms before looping to prevent text flashing or parallel line signal noise
}

// Low-level helper block to remove sleep bit from MPU-6050 power registry
void initMPU(int addr) {
  Wire.beginTransmission(addr); // Establish bus data target line connection
  Wire.write(0x6B);             // Direct signal to PWR_MGMT_1 internal memory register
  Wire.write(0);                // Clear byte array flags to 0 to disable standby/sleep mode
  Wire.endTransmission(true);   // Complete bus transfer routine and free line
}

// Mathematical calculation block to extract clean Pitch tilt degrees from raw G-force data
float getPitch(int addr) {
  Wire.beginTransmission(addr); // Open communications with target sensor path address
  Wire.write(0x3B);             // Request focus begin on raw Accel X high data register address
  if (Wire.endTransmission(false) != 0) { // Check I2C transfer acknowledgement state
    return 0.0;                 // If bus line failure check triggers, exit safely with 0 angle
  }
  Wire.requestFrom(addr, 6, true); // Demand a chunk dump of 6 registers (X, Y, Z data blocks)
  
  if (Wire.available() < 6) return 0.0; // Fallback exit routine if registers read empty
  
  // Reconstruct individual 8-bit registers back into full 16-bit whole signed integers
  int16_t rawX = Wire.read() << 8 | Wire.read(); // Merge X axis register high and low data
  int16_t rawY = Wire.read() << 8 | Wire.read(); // Merge Y axis register high and low data
  int16_t rawZ = Wire.read() << 8 | Wire.read(); // Merge Z axis register high and low data
  
  // Map raw sensor scale factor bits down to unified real-world earth G-Forces
  float x = rawX / 16384.0;     // Divide by scale factor constant at standard +/-2g profile
  float y = rawY / 16384.0;     // Divide by scale factor constant at standard +/-2g profile
  float z = rawZ / 16384.0;     // Divide by scale factor constant at standard +/-2g profile
  
  // Use trigonometry to calculate the absolute angular pitch orientation in human degrees
  float pitch = atan2(-x, sqrt(y * y + z * z)) * 180.0 / PI;//atan2 is mean arctan with 2 component -x, sqrt(y * y + z * z)
  return pitch;
}
