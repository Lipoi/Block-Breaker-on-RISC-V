#include "lcd/lcd.h"
#include <string.h>
#include "utils.h"
#include <time.h>
#include <stdlib.h>
/*Setting: 
Size: 160x80
Top-left point is (0, 0), while bottom-right is (159, 79)
Color setting: RGB565. Link: http://www.barth-dev.de/online/rgb565-color-picker/
*/
int pre_Ballcenter[2] = {80,39};
int Ballcenter[2] = {80,39};
int radius = 2; // The radius = 2, we can change it later.
int pre_PadAcenter[2] = {4,39};
int pre_PadBcenter[2] = {155,39};
int PadAcenter[2] = {4,39}; // Center of paddle A. We can first use Showline(may be Showrectangle is also ok).
int PadBcenter[2] = {155,39}; // I use center insteat of (x1,y1)(x1,y2) in case we maybe change the length of paddle later.
int Padlength = 16; // The length of paddle A 
// We can even let the length of A and B different!
int yourScore = 0;
int oppositeScore = 0;
int maxScore = 10; // The condition to win(changeable)
u8 wingame; // youwin = 1 if you win; =0 if you lose
u8 winball;

float ballspeed_x=1; //define the velocity of the ball
float ballspeed_y=0; 

float paddlemaxspeed = 1;

bool whowins = 0;

int AddOppositeScore(int a);
int AddYourScore(int a);
int PadbcenterPadlengthCheckUp(int *padbcenter,int padlength);
int PadbcenterPadlengthCheckDown(int *padbcenter,int padlength);
int getPadBcenter1(int padBcenter);
int AddPadBcenter(int a);
int SubPadBcenter(int *padBcenter);
int SubBallspeedy(int ballspeed_y);
int SubBallspeedx(int ballspeed_x);
int AddBallspeedx(int ballspeed_x,int *ballcenter);
int AddBallspeedy(int ballspeed_y,int *ballcenter);
int setWinball(int winball);
int getBallcenter0(int ballcenter);
int getBallcenter1(int *ballcenter);
//some useless codes
int getpaddlespeed(int speed);
int checkballspeedx(int ballspeedx);
int checkballspeedy(int ballspeedy);
int checkballspeed(int ballspeed);
int setloseball(int loseball);
int subpaddlespeedx(int paddlespeedx);
int subpaddlespeedy(int paddlespeedy);



void Inp_init(void)
{
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) 
{
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1);
    RCU_CFG0|=(0b10<<14)|(1<<28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0)|=ADC_CTL1_ADCON;
}

void IO_init(void)
{
    Inp_init(); // inport init
    Adc_init(); // A/D init
    Lcd_Init(); // LCD init
}

void PadBAct(){
    //int checkup = PadbcenterPadlengthCheckUp(PadBcenter,Padlength);
    //if(Get_Button(0) && ((checkup) >= 77)){}

    if(Get_Button(0) && ((PadBcenter[1] + Padlength/2) >= 77)){}
    else if(Get_Button(1) && ((PadBcenter[1] - Padlength/2) <= 2)){}
    else if(Get_Button(0) && Get_Button(1)){}
    else if(Get_Button(0)){
    int a = PadBcenter[1];
    pre_PadBcenter[1] = getPadBcenter1(a); 
    //pre_PadBcenter[1] = PadBcenter[1];
    //int score;
    //score = AddPadBcenter(score);
    PadBcenter[1] += 1;

    //LCD_DrawLine(pre_PadBcenter[0], pre_PadBcenter[1]/1 - Padlength/2, pre_PadBcenter[0], pre_PadBcenter[1]/1 + Padlength/2, BLACK); 
    //LCD_DrawLine(PadBcenter[0], PadBcenter[1]/1 - Padlength/2, PadBcenter[0], PadBcenter[1]/1 + Padlength/2, WHITE); 
    }
    else if(Get_Button(1)){
    pre_PadBcenter[1] = PadBcenter[1]; PadBcenter[1] -= 1;
    //LCD_DrawLine(pre_PadBcenter[0], pre_PadBcenter[1]/1 - Padlength/2, pre_PadBcenter[0], pre_PadBcenter[1]/1 + Padlength/2, BLACK); 
    //LCD_DrawLine(PadBcenter[0], PadBcenter[1]/1 - Padlength/2, PadBcenter[0], PadBcenter[1]/1 + Padlength/2, WHITE); 
    }
    LCD_DrawLine(pre_PadBcenter[0]/1, pre_PadBcenter[1]/1 - Padlength/2, pre_PadBcenter[0]/1, pre_PadBcenter[1]/1 + Padlength/2, BLACK);
    LCD_DrawLine(PadBcenter[0]/1, PadBcenter[1]/1 - Padlength/2, PadBcenter[0]/1, PadBcenter[1]/1 + Padlength/2, WHITE); 
}

void BALLACT()
{
    if(Ballcenter[1] <= 2 || Ballcenter[1] >= 77){
        //ballspeed_y = SubBallspeedy(ballspeed_y);
        ballspeed_y = (-ballspeed_y);
        }
    if(Ballcenter[0] <= 7 || Ballcenter[0] >= 152){
        if(Ballcenter[1] > (PadBcenter[1]+Padlength/2+2) || Ballcenter[1] < (PadBcenter[1]-Padlength/2-2) || Ballcenter[1] > (PadBcenter[1]+Padlength/2+2) || Ballcenter[1] < (PadBcenter[1]-Padlength/2-2)){
            if(Ballcenter[0] <= 7){yourScore++; winball = 1;return;}
            if(Ballcenter[0] >= 152){
                //void AddOppositeScore(u16 oppositescore)
                //oppositeScore++; 
                oppositeScore = AddOppositeScore(oppositeScore);
                //winball = setWinball(winball);
                winball = 1;
                return;
                }
        }
        ballspeed_x = (-ballspeed_x); 
        ballspeed_y += (rand()%4+2)/2;
    }
    //Ballcenter[0] = AddBallspeedx(ballspeed_x,Ballcenter);
    Ballcenter[0] += ballspeed_x;
    Ballcenter[1] += ballspeed_y;
    int ballcen = Ballcenter[0];
    pre_Ballcenter[0] =  getBallcenter0(ballcen);
    //pre_Ballcenter[0] = Ballcenter[0];
    pre_Ballcenter[1] = Ballcenter[1];
}

int main()
{
    IO_init();         // init OLED
    // YOUR CODE HERE
    LCD_Clear(BLACK);
    u8 retry = 1;
    char* diff = "Choose difficulty";
    LCD_ShowString(10,40,diff,WHITE);
    delay_1ms(2000);
    LCD_Clear(BLACK);
    for (int i = 1; i <= 3; i++)
    {
        LCD_ShowNum(60,40,4-i,2,WHITE);
        delay_1ms(1000);
        LCD_Clear(BLACK);
        if(Get_Button(0)){paddlemaxspeed = 0.5;}
        if(Get_Button(1)){paddlemaxspeed = 1;}
        if(Get_Button(0) && Get_Button(1)){paddlemaxspeed = 2;}
    }
    LCD_Clear(BLACK);
    char* st = "START!";
    LCD_ShowString(40,40,st,WHITE);
    delay_1ms(2000);
    
    
    
    while (retry == 1) // rerun the game if retry = 1
    {   
        retry = 0;
        LCD_Clear(BLACK);
        BACK_COLOR=BLACK;
        Ballcenter[0] = 80; Ballcenter[1] = 39;
        LCD_DrawRectangle(2,2,157,77,BLUE);
        LCD_DrawLine(80, 2, 80, 157, GRAY);
        LCD_ShowNum(70,7,oppositeScore,1,WHITE);
        LCD_ShowNum(84,7,yourScore,1,WHITE);
        LCD_DrawLine(PadAcenter[0], PadAcenter[1] - Padlength/2, PadAcenter[0], PadAcenter[1] + Padlength/2, WHITE);
        LCD_DrawLine(PadBcenter[0], PadBcenter[1] - Padlength/2, PadBcenter[0], PadBcenter[1] + Padlength/2, WHITE);
        while (!Get_BOOT0()) //
        {
            if(winball == 1){winball = 0; 
            Ballcenter[0] = 80; Ballcenter[1] = 39;
            pre_Ballcenter[0] = 80; pre_Ballcenter[1] = 39;
            ballspeed_x = (rand()%4+2)/2;
            ballspeed_y = (rand()%4+2)/4;
            PadAcenter[0] = 4; PadAcenter[1] = 39;
            pre_PadAcenter[0] = 4; pre_PadAcenter[1] = 39;
            LCD_DrawLine(155,2,155,77,BLACK);
            LCD_DrawLine(4,2,4,77,BLACK);
            LCD_DrawLine(PadAcenter[0], PadAcenter[1] - Padlength/2, PadAcenter[0], PadAcenter[1] + Padlength/2, WHITE);
            LCD_Clear(BLACK);
            continue;}
            LCD_DrawRectangle(2,2,157,77,BLUE);
            LCD_ShowNum(70,7,oppositeScore,1,WHITE);
            LCD_ShowNum(84,7,yourScore,1,WHITE);
            if(yourScore == 10){break;}
            if(oppositeScore == 10){break;}
            LCD_DrawLine(80, 2, 80, 157, GRAY);
            PadBAct();
            //LCD_Fill(Ballcenter[0]-2, Ballcenter[1] - 2, Ballcenter[0] + 2, Ballcenter[1] + 2, BLACK);
            LCD_DrawCircle(pre_Ballcenter[0], pre_Ballcenter[1], radius, BLACK);
            BALLACT();
            LCD_DrawCircle(Ballcenter[0], Ballcenter[1], radius, WHITE);
            //LCD_DrawCircle(pre_Ballcenter[0], pre_Ballcenter[1], radius, BLACK);
            delay_1ms(100/20);
            //LCD_Clear(BLACK);
            //LCD_Fill(Ballcenter[0]-5, Ballcenter[1] - 5, Ballcenter[0] + 5, Ballcenter[1] + 5, BLACK);
            //LCD_DrawCircle(pre_Ballcenter[0]/1, pre_Ballcenter[1]/1, radius, BLACK);
            LCD_DrawLine(pre_PadAcenter[0], pre_PadAcenter[1] - Padlength/2, pre_PadAcenter[0], pre_PadAcenter[1] + Padlength/2, BLACK);
            if((PadAcenter[1] + Padlength/2 >= 77)&&(ballspeed_y > 0) || (PadAcenter[1] - Padlength/2 <= 2) && ballspeed_y < 0){}
            else if(Ballcenter[1] > PadAcenter[1] && paddlemaxspeed < ballspeed_y){PadAcenter[1] += paddlemaxspeed; pre_PadAcenter[1] = PadAcenter[1];}
            else if (Ballcenter[1] < PadAcenter[1] && paddlemaxspeed < -ballspeed_y){PadAcenter[1] -= paddlemaxspeed; pre_PadAcenter[1] = PadAcenter[1];}
            else
            {
                PadAcenter[1] += ballspeed_y; pre_PadAcenter[1] = PadAcenter[1];
            }
            LCD_DrawLine(PadAcenter[0], PadAcenter[1] - Padlength/2, PadAcenter[0], PadAcenter[1] + Padlength/2, WHITE);
            if(yourScore >= 5 || oppositeScore >= 5){break;}
        } // exit if one win

        LCD_Clear(BLACK);
        char* win = "YOU WIN!";
        char* lose = "YOU LOSE!";
        char* re = "WANT RETRY?";
        if(yourScore >= 5){LCD_ShowString(40, 40, win, WHITE);}
        if(oppositeScore >= 5){LCD_ShowString(40,40, lose, WHITE);}
        yourScore = 0; oppositeScore = 0;
        delay_1ms(5000);
        //IfRetry(); // Show some words, rectangle... to let player choose whether retry
        while (!Get_BOOT0())
        {
            delay_1ms(50);
            LCD_ShowString(20,40,re,WHITE);
            if(Get_Button(0)){retry = 1; LCD_Clear(BLACK); break;} // If press button 0, we retry the game.
            if(Get_Button(1)){LCD_Clear(BLACK); break;} // If press button 1, no retry, end the game.
        }
    }
    return 0;
}
