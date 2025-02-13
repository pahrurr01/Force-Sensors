#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90393.h>

Adafruit_MLX90393 sensor = Adafruit_MLX90393();

void setup(void)
{
  Serial.begin(115200);

  // Menunggu hingga Serial siap
  while (!Serial) {
     // Tidak perlu delay, hanya menunggu koneksi serial
  }

  if (!sensor.begin_I2C()) {
    Serial.println("No sensor found ... check your wiring?");
    while (1) { delay(10); } // Menahan eksekusi jika sensor tidak ditemukan
  }

  Serial.println("Found a MLX90393 sensor");

  sensor.setGain(MLX90393_GAIN_1X);
  
  // Menampilkan pengaturan gain
  Serial.print("Gain set to: ");
  switch (sensor.getGain()) {
    case MLX90393_GAIN_1X: Serial.println("1 x"); break;
    case MLX90393_GAIN_1_33X: Serial.println("1.33 x"); break;
    case MLX90393_GAIN_1_67X: Serial.println("1.67 x"); break;
    case MLX90393_GAIN_2X: Serial.println("2 x"); break;
    case MLX90393_GAIN_2_5X: Serial.println("2.5 x"); break;
    case MLX90393_GAIN_3X: Serial.println("3 x"); break;
    case MLX90393_GAIN_4X: Serial.println("4 x"); break;
    case MLX90393_GAIN_5X: Serial.println("5 x"); break;
  }

  // Mengatur resolusi dan sensitivitas
  sensor.setResolution(MLX90393_X, MLX90393_RES_17);
  sensor.setResolution(MLX90393_Y, MLX90393_RES_17);
  sensor.setResolution(MLX90393_Z, MLX90393_RES_16);

  // Mengatur oversampling dan filter digital
  sensor.setOversampling(MLX90393_OSR_3);
  sensor.setFilter(MLX90393_FILTER_5);
}

void loop(void) {
  sensors_event_t event;
  
  // Membaca data sensor
  if (sensor.getEvent(&event)) {
   // Serial.print(millis());  // Menampilkan waktu sejak program mulai
   // Serial.print(",");
    Serial.print(" X: "); Serial.print(event.magnetic.x, 2);
    Serial.print(",");
    Serial.print(" Y: "); Serial.print(event.magnetic.y, 2);
    Serial.print(",");
    Serial.print(" Z: "); Serial.println(event.magnetic.z, 2);
  } else {
    Serial.println("Unable to read XYZ data from the sensor.");
  }

  // delay(100);  // Menambahkan sedikit delay jika diperlukan
}
