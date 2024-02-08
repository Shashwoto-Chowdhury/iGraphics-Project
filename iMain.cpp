# include "iGraphics.h"
# include<windows.h>
# include<mmsystem.h>
# pragma comment(lib, "Winmm.lib")
# define screen_width 840
# define screen_height 770
# define asteroid_number 4
# define bullet_number 500
//# include "stb_image.h"
struct asteroids{
	double x;
	double y;
	bool alive,in=false;
	double dx=5,dy=5;
};
struct f_bullet{
	double x,y;
	bool bullet_show=false;
};

double space_x=370;
double space_y=0;

int space_health=200;
double health_x=650;
double health_y=710; 

int cnt=0;
asteroids asteroid[asteroid_number];
f_bullet own_bullet[bullet_number];
int score=0;
double score_x=650;
double score_y=740;

double collision_x,collision_y;
bool collision_check=false;
int col_cnt=0;



int page_state=0;
bool music_on=true;
bool gmusic_on=true;
bool pause=false;

char lobby_sound[30]="sounds\\lobby.wav";
char game_sound[30]="sounds\\In game.wav";

char img[5][30]={"images\\home.bmp","images\\gamebg.bmp","images\\home.bmp","images\\home.bmp","images\\home.bmp"};
char play[30]="images\\play.bmp";
char high_score[30]="images\\high_score.bmp";
char settings[30]="images\\settings.bmp";
char instructions[30]="images\\instructions.bmp";
char quit[30]="images\\quit.bmp";
char title[30]="images\\title.bmp";
char back[30]="images\\return.bmp";
char s_title[30]="images\\sTitle.bmp";
char l_music[30]="images\\lobbymusic.bmp";
char g_music[30]="images\\gamemusic.bmp";
char volume[30]="images\\volume.bmp";
char mute[30]="images\\mute.bmp";
char spaceship[30]="images\\spaceship.bmp";
char asteroid_image[30]="images\\asteroid.bmp";
char my_bullet[30]="images\\sbullet.bmp";
char collision[30]="images\\collision.bmp";

char score_text[30]="Score: 0";
char health[30]="Health: 200";



void asteroid_show()
{
	int i;
	for(i=0;i<asteroid_number;i++){
		if(asteroid[i].alive){
			iShowBMP2(asteroid[i].x,asteroid[i].y,asteroid_image,0);
		}
	}
}
void bulletshow()
{
	int i;
	for(i=1;i<bullet_number;i++){
		if(own_bullet[i].bullet_show){
			iShowBMP2(own_bullet[i].x,own_bullet[i].y,my_bullet,0);
		}
	}
}
void iDraw() {
	//place your drawing codes here
	iClear();
	if(page_state==0){
		iShowBMP(0,0,img[page_state]);
		iShowBMP2(120,620,title,0);
		iShowBMP2(235,510,play,0);
		iShowBMP2(235,390,high_score,0);
		iShowBMP2(235,270,settings,0);
		iShowBMP2(235,150,instructions,0);
		iShowBMP2(235,30,quit,0);

	}
	if(page_state==1){
		iShowBMP(0,0,img[page_state]);
		iShowBMP2(space_x,space_y,spaceship,0);
		iSetColor(44,166,43);
		iText(score_x,score_y,score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,255,255);
		iText(health_x,health_y,health,GLUT_BITMAP_TIMES_ROMAN_24);
		asteroid_show();
		bulletshow();
		if(collision_check){
			iShowBMP2(collision_x,collision_y,collision,0);
			col_cnt++;
			if(col_cnt==10){
				collision_check=false;
				col_cnt=0;
			}
		}
	}
	if(page_state==2){
		iShowBMP(0,0,img[page_state]);
		iShowBMP2(212.5,100,back,0);
	}

	if(page_state==3){
		iShowBMP(0,0,img[page_state]);
		iShowBMP(0,624,s_title);
		iShowBMP2(130,524,l_music,0);
		if(music_on){
			iShowBMP2(604,524,volume,0);
		}
		else{
			iShowBMP2(604,524,mute,0);
		}
		iShowBMP2(130,424,g_music,0);
		if(gmusic_on){
			iShowBMP2(604,424,volume,0);
		}
		else{
			iShowBMP2(604,424,mute,0);
		}

		iShowBMP2(212.5,100,back,0);
	}
	if(page_state==4){
		iShowBMP(0,0,img[page_state]);
		iShowBMP2(212.5,100,back,0);
		
	}
	//iText(40, 40, "Hi, I am iGraphics");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void bullet_initialize()
{
	
	own_bullet[cnt].x=space_x+45;
	own_bullet[cnt].y=90;
	own_bullet[cnt].bullet_show=true;
	cnt++;
	if(cnt>=bullet_number)cnt=1;
	
}
void asteroid_initialize()
{
	int i;
	for(i=0;i<asteroid_number;i++){
		asteroid[i].x=rand()%800;
		asteroid[i].y=screen_height+rand()%200;
		asteroid[i].alive=true;
	}
}
void bullet_clear()
{
	int i;
	for(i=0;i<bullet_number;i++){
		own_bullet[i].y=-20;
		own_bullet[i].bullet_show=false;
	}
}
void asteroid_clear()
{
	int i;
	for(i=0;i<asteroid_number;i++){
		asteroid[i].in=false;
		asteroid[i].alive=false;
		asteroid[i].dx=5;
		asteroid[i].dy=5;
	}
}
void score_clear()
{
	score=0;
	sprintf(score_text,"Score: %d",score);
}
void health_init()
{
	space_health=200;
	sprintf(health,"Health: %d",space_health);
}

void iMouse(int button, int state, int mx, int my) {
	if(page_state==0){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=30&&my<=130){
			exit(0);
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=510&&my<=610){
			page_state=1;
			asteroid_initialize();
			if(gmusic_on){
				PlaySound(game_sound, NULL , SND_LOOP|SND_ASYNC);
			}
			else{
			 	PlaySound(0,0,0);
			}
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=390&&my<=490){
			page_state=2;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=270&&my<=370){
			page_state=3;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=150&&my<=250){
			page_state=4;
		}
	}
	if(page_state==1){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(!pause)bullet_initialize();
		}
	}
	if(page_state==3){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=212.5&&mx<=627.5&&my>=100&&my<=200){
			page_state=0;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=604 && mx<=697 && my>=524 && my<=624){
			if(music_on){
				PlaySound(0,0,0);
				music_on=false;
			}
			else{
				PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
				music_on=true;
			}
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=604 && mx<=697 && my>=424 && my<=524){
			if(gmusic_on){
				//PlaySound(0,0,0);
				gmusic_on=false;
			}
			else{
				//PlaySound(game_sound, NULL , SND_LOOP|SND_ASYNC);
				gmusic_on=true;
			}
		}
	}

}

void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	if(page_state==1){
		if(key == 'a'){
			if(!pause){
				space_x-=5;
				if(space_x<=0){
					space_x=0;
				}
			}
		}
		if(key == 'd'){
			if(!pause){
				space_x+=5;
				if(space_x>=(screen_width-90)){
					space_x=screen_width-90;
				}
			}
		}
		if(key == 'w'){
			page_state=0;
			cnt=0;
			bullet_clear();
			asteroid_clear();
			score_clear();
			health_init();
		}
		if(key == 'p'){
			if(pause){
				pause=false;
			}
			else{
				pause=true;
			}
		}
	}
	
	//place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key) {

	
}

void asteroid_change()
{
	int i;
	if(page_state==1 && !pause){
		for(i=0;i<asteroid_number;i++){
			if(asteroid[i].alive){
				asteroid[i].x-=asteroid[i].dx;
				asteroid[i].y-=asteroid[i].dy;
				if(asteroid[i].y<(screen_height-40)&&asteroid[i].in==false)
					asteroid[i].in=true;
				if(asteroid[i].x<=0 || asteroid[i].x>=(screen_width-40))
					asteroid[i].dx*=(-1);
				if(asteroid[i].y<=0||(asteroid[i].y>=(screen_height-40)&&asteroid[i].in==true))
					asteroid[i].dy*=(-1);
			}
			else{
				asteroid[i].x=rand()%800;
				asteroid[i].y=screen_height+rand()%200;
				asteroid[i].alive=true;
			}
		}
			
	}
}

void bullet_change()
{
	int i;
	if(page_state==1 && !pause){
		for(i=1;i<bullet_number;i++){
			if(own_bullet[i].bullet_show){
				own_bullet[i].y+=5;
				if(own_bullet[i].y>=screen_height){
					own_bullet[i].bullet_show=false;
					own_bullet[i].y=-20;
				}
			}
		}
	}
}

void asteroid_collision_check()
{
	int i,j;
	if(page_state==1 && !pause){
		for(i=1;i<bullet_number;i++){
			if(own_bullet[i].bullet_show){
				for(j=0;j<asteroid_number;j++){
					if((own_bullet[i].x+10 > asteroid[j].x && own_bullet[i].x < asteroid[j].x+40) && (own_bullet[i].y+15 > asteroid[j].y && own_bullet[i].y < asteroid[j].y+40)){
						own_bullet[i].bullet_show=false;
						collision_check=true;
						own_bullet[i].y=-20;
						asteroid[j].alive=false;
						asteroid[j].dx=5;
						asteroid[j].dy=5;
						collision_x=asteroid[j].x;
						collision_y=asteroid[j].y;
						asteroid[j].in=false;
						score+=10;
						sprintf(score_text,"Score: %d",score);
						break;
					}
				}
			}
		}
	}
}

void spaceship_collision()
{
	int i;
	if(page_state==1 && !pause){
		for(i=0;i<asteroid_number;i++){
			if((space_x+90 > asteroid[i].x && space_x < asteroid[i].x+40) && (space_y+90 > asteroid[i].y && space_y < asteroid[i].y+40)){
				asteroid[i].alive=false;
				asteroid[i].dx=5;
				asteroid[i].dy=5;
				collision_x=asteroid[i].x;
				collision_y=asteroid[i].y-10;
				collision_check=true;
				asteroid[i].in=false;
				space_health-=10;
				sprintf(health,"Health: %d",space_health);
				break;
			}
		}
	}
}


int main() {
	iSetTimer(25,asteroid_change);
	iSetTimer(25,bullet_change);
	iSetTimer(25,asteroid_collision_check);
	iSetTimer(25,spaceship_collision);
	if(music_on){
		PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
	}
	
	iInitialize(screen_width, screen_height, "Asteroid Game");
	//place your own initialization codes here.
	return 0;
}
