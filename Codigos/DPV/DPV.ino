const int pwmPin = 9;  // Pin PWM en Arduino (ajustar según la placa)

// Parámetros de voltamperometría DPV
const int V_start = 0;       // Valor inicial del PWM (0 equivale a 0 V)
const int V_end = 255;       // Valor final del PWM (255 equivale a 5 V en Arduino)
const int num_steps = 30;    // Número de escalones para la subida y bajada (30 escalones)
const int pulse_amp = 10;    // Amplitud del pulso
const int t_pulse = 200;     // Duración del pulso diferencial (200 ms)
const int t_step = 200;      // Duración de cada paso (200 ms)
const int scan_rate = 1;     // Tasa de escaneo (puedes ajustarlo si es necesario)

void set_pwm(int val) {
    analogWrite(pwmPin, val);  // En Arduino, el PWM va de 0 a 255
}

void setup() {
    pinMode(pwmPin, OUTPUT);
}

void loop() {
    // Rampa de subida escalonada con pulsos diferenciales
    for (int i = 0; i <= num_steps; i++) {
        int pwm_value = map(i, 0, num_steps, V_start, V_end); // Mapea la muestra a un valor de PWM
        set_pwm(pwm_value);  // Establece el PWM
        delay(t_step);  // Espera el tiempo correspondiente para la siguiente muestra

        // Aplicar el pulso diferencial
        int pulse_val = pwm_value + pulse_amp;
        if (pulse_val > V_end) {
            pulse_val = V_end;
        }
        set_pwm(pulse_val);  // Establece el pulso
        delay(t_pulse);      // Duración del pulso

        set_pwm(pwm_value);  // Regresa al valor base
    }

    // Rampa de bajada escalonada con pulsos diferenciales
    for (int i = 0; i <= num_steps; i++) {
        int pwm_value = map(i, 0, num_steps, V_end, V_start); // Mapea la muestra a un valor de PWM (bajando)
        set_pwm(pwm_value);  // Establece el PWM
        delay(t_step);  // Espera el tiempo correspondiente para la siguiente muestra

        // Aplicar el pulso diferencial
        int pulse_val = pwm_value + pulse_amp;
        if (pulse_val > V_end) {
            pulse_val = V_end;
        }
        set_pwm(pulse_val);  // Establece el pulso
        delay(t_pulse);      // Duración del pulso

        set_pwm(pwm_value);  // Regresa al valor base
    }
}
