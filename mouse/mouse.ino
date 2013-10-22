

// BlackBerry Track Ball 

//  Pin Assignments
#define TB_DIR_RIGHT 45
#define TB_DIR_LEFT 44
#define TB_DIR_DOWN 43
#define TB_DIR_UP 42

// Click assignment
#define TB_CMD 20

// LED's OUT Pins
#define TB_LED_WHITE 14
#define TB_LED_GREEN 13
#define TB_LED_RED 12
#define TB_LED_BLUE 11

//Mouse buttons
#define MSB_LEFT 21
#define MSB_CENTER 22
#define MSB_RIGHT 23

//int bt1 = 9;

bool active=true;

/* TrackBall */
struct TBState
{
	/* current state */
	int up, down, left, right;
	
	/* cumulated state */
	int c_up, c_down, c_left, c_right;
} tbState;

void initTB()
{
	pinMode(TB_DIR_UP, INPUT);
	pinMode(TB_DIR_DOWN, INPUT);
	pinMode(TB_DIR_LEFT, INPUT);
	pinMode(TB_DIR_RIGHT, INPUT);
        pinMode(TB_CMD, INPUT);
	
	pinMode(TB_LED_BLUE, OUTPUT);
	pinMode(TB_LED_RED, OUTPUT);
	pinMode(TB_LED_GREEN, OUTPUT);
	pinMode(TB_LED_WHITE, OUTPUT);
	
	tbState.up = digitalRead(TB_DIR_UP);
	tbState.down = digitalRead(TB_DIR_DOWN);
	tbState.left = digitalRead(TB_DIR_LEFT);
	tbState.right = digitalRead(TB_DIR_RIGHT);
	
	//digitalWrite(TB_LED_WHITE, HIGH);
}

void pollTB(bool sendEvents=true)
{
	struct TBState newState = tbState;
	const int threshold = 1;//3
	bool reset = false;
	
	newState.up = digitalRead(TB_DIR_UP);
	newState.down = digitalRead(TB_DIR_DOWN);
	newState.left = digitalRead(TB_DIR_LEFT);
	newState.right = digitalRead(TB_DIR_RIGHT);
        
	//struct event tb_event;
	//tb_event.type = TRACKBALL_MOVED;
	if (newState.up != tbState.up) {
                newState.c_up++;
		if (newState.c_up > threshold)
		{        
                        Serial.print("Mouse UP ");
                        Mouse.move(0,10);
                        reset = true;
		}
	}
	if (newState.down != tbState.down) {
		newState.c_down++;
		if (newState.c_down > threshold)
		{
			Serial.print("Mouse DOWN ");
                        Mouse.move(0,-10);
                        reset = true;
		}
	}
	if (newState.left != tbState.left) {
		newState.c_left++;
		if (newState.c_left > threshold)
		{
			Serial.print("Mouse LEFT ");
                        Mouse.move(-10,0);
                        reset = true;
		}
	}
	if (newState.right != tbState.right) {
		newState.c_right++;
		if (newState.c_right > threshold)
		{
  			Serial.print("Mouse RIGHT ");
                        Mouse.move(10,0);
                        reset = true;
		}
	}
	
	if (reset)
	{
		newState.c_up = 0;
		newState.c_down = 0;
		newState.c_left = 0;
		newState.c_right = 0;
                Serial.print(".\n");
	}
		
	tbState = newState;
}

/* Mouse Buttons */
struct MSBState
{
	/* current state */
	int left, right, center;
	
	/* cumulated state */
	int c_left, c_right, c_center;
} msbState;

void initMSB()
{
	pinMode(MSB_LEFT, INPUT);
	pinMode(MSB_CENTER, INPUT);
	pinMode(MSB_RIGHT, INPUT);
	
	msbState.left = digitalRead(MSB_LEFT);
	msbState.right = digitalRead(MSB_RIGHT);
	msbState.center = digitalRead(MSB_CENTER);

}

void pollMSB(bool sendEvents=true)
{
	struct MSBState newState = msbState;
	const int threshold = 1;//3
	bool reset = false;
	
	newState.left = digitalRead(MSB_LEFT);
	newState.right = digitalRead(MSB_RIGHT);
	newState.center = digitalRead(MSB_CENTER);

	if (newState.left != msbState.left) {
		newState.c_left++;
		if (newState.c_left > threshold)
		{
			Serial.print("LEFT CLICK");
                        reset = true;
		}
	}
	if (newState.right != msbState.right) {
		newState.c_right++;
		if (newState.c_right > threshold)
		{
  			Serial.print("RIGHT CLICK");
                        reset = true;
		}
	}
	if (newState.center != msbState.center) {
		newState.c_center++;
		if (newState.c_center > threshold)
		{
  			Serial.print("CENTER CLICK");
                        reset = true;
		}
	}
	
	if (reset)
	{
		newState.c_left = 0;
		newState.c_right = 0;
		newState.c_center = 0;
                Serial.print(" .\n");
	}
		
	msbState = newState;
}


void setup() {        
  Serial.begin(9600);	  
  
  initTB(); 
  initMSB();
  
}


void loop() {
  /* the track ball */
  pollTB();
  pollMSB();
  
//  Serial.print("Poll: (");
//  Serial.print(digitalRead(TB_DIR_UP)); Serial.print(",");
//  Serial.print(digitalRead(TB_DIR_DOWN)); Serial.print(",");
//  Serial.print(digitalRead(TB_DIR_LEFT)); Serial.print(",");
//  Serial.print(digitalRead(TB_DIR_RIGHT)); Serial.print(")\n");

  if(digitalRead(TB_CMD)==0)
    {
    Serial.print("TrackBall BUTTON = ");
    if(active) {
      active=false;
      Serial.print("true\n");
    }
    else {
      active=true;
      Serial.print("false\n");
    }
    delay(300);
    }
    
  if(active) {
    digitalWrite(TB_LED_BLUE, HIGH);
  }
  else {
    digitalWrite(TB_LED_BLUE, LOW);
  }

}
