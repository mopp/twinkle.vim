// VFDの切り替えピン番号
const int VFD_PIN_G1 = 2;
const int VFD_PIN_G2 = 4;
const int VFD_PIN_G3 = 5;
const int VFD_PIN_G4 = 6;
const int VFD_PIN_G5 = 7;
const int VFD_PIN_G6 = 8;
const int VFD_PINS[6] = {
    VFD_PIN_G1,
    VFD_PIN_G2,
    VFD_PIN_G3,
    VFD_PIN_G4,
    VFD_PIN_G5,
    VFD_PIN_G6,
};
const int VFD_PIN_NUM = sizeof(VFD_PINS) / sizeof(VFD_PINS[0]);

// VFDのセグメントピン番号
const int VFD_SEG_PIN_A  = 9;
const int VFD_SEG_PIN_B  = 10;
const int VFD_SEG_PIN_C  = 12;
const int VFD_SEG_PIN_D  = A5;
const int VFD_SEG_PIN_E  = A4;
const int VFD_SEG_PIN_F  = A0;
const int VFD_SEG_PIN_G  = A1;
const int VFD_SEG_PIN_MN = A3;
const int VFD_SEG_PIN_DP = A2;
const int VFD_SEG_PINS[] = {
    VFD_SEG_PIN_A,
    VFD_SEG_PIN_B,
    VFD_SEG_PIN_C,
    VFD_SEG_PIN_D,
    VFD_SEG_PIN_E,
    VFD_SEG_PIN_F,
    VFD_SEG_PIN_G,
    VFD_SEG_PIN_MN,
    VFD_SEG_PIN_DP,
};
const int VFD_SEG_NUM = sizeof(VFD_SEG_PINS) / sizeof(VFD_PINS[0]);

// 各VFDを点灯させるPINの組み合わせ
const int VFD_PATTERNS[][VFD_SEG_NUM] = {
    {1, 1, 1, 1, 1, 1, 0, 0, 0},    // 0
    {0, 1, 1, 0, 0, 0, 0, 0, 0},    // 1
    {1, 1, 0, 1, 1, 0, 1, 0, 0},    // 2
    {1, 1, 1, 1, 0, 0, 1, 0, 0},    // 3
    {0, 1, 1, 0, 0, 1, 1, 1, 0},    // 4
    {1, 0, 1, 1, 0, 1, 1, 0, 0},    // 5
    {1, 0, 1, 1, 1, 1, 1, 0, 0},    // 6
    {1, 1, 1, 0, 0, 0, 0, 0, 0},    // 7
    {1, 1, 1, 1, 1, 1, 1, 0, 0},    // 8
    {1, 1, 1, 1, 0, 1, 1, 0, 0},    // 9
};
const int VFD_PATTERN_NUM = sizeof(VFD_PATTERNS) / sizeof(VFD_PATTERNS[0]);

// シリアルポートから受け取った数字を保持
int buf[VFD_PIN_NUM] = {0}, buf_cnt = 0;


void setup() {
    for (int i = 0; i < VFD_PIN_NUM; ++i) {
        pinMode(VFD_PINS[i], OUTPUT);
        digitalWrite(VFD_PINS[i], LOW);
    }

    // 9番pin(VFD_SEG_PIN_A)は初期化しないほうがいいらしい... :(
    for (int i = 1; i < VFD_SEG_NUM; ++i) {
        pinMode(VFD_SEG_PINS[i], OUTPUT);
        digitalWrite(VFD_SEG_PINS[i], LOW);
    }

    Serial.begin(9600);
    delay(5000);
    Serial.println("Finish Setup");
}


void loop() {
    if (0 < Serial.available()) {
        int t = Serial.read();

        if (buf_cnt == VFD_PIN_NUM || t == '\n') {
            // カウンタ初期化
            buf_cnt = 0;
        }

        if ('0' <= t && t <= '9') {
            // 文字コードが来るので数字に変換
            buf[buf_cnt++] = t - '0';
        }
    }

    // bufの値を表示
    for (int i = 0; i < VFD_PIN_NUM; ++i) {
        light_vfd(VFD_PINS[VFD_PIN_NUM - 1 - i], buf[i], false);
    }
}


inline void light_vfd(const int vfd_pin, const int num, const boolean isDot) {
    // 表示するVFD管のピンを有効に
    for (int i = 0; i < VFD_PIN_NUM; ++i) {
        digitalWrite(VFD_PINS[i], LOW);
    }
    digitalWrite(vfd_pin, HIGH);

    if (isDot == true) {
        digitalWrite(VFD_SEG_PIN_DP, HIGH);
    }

    // 指定された数字を表示 dotのぶんを-1
    for (int i = 0; i < VFD_SEG_NUM - 1; ++i) {
        digitalWrite(VFD_SEG_PINS[i], (VFD_PATTERNS[num][i] == 1 ? HIGH : LOW));
    }

    delayMicroseconds(800);
}
