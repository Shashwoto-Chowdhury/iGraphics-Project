# include "iGraphics.h"
# include<windows.h>
# include<mmsystem.h>
# pragma comment(lib, "Winmm.lib")
# define screen_width 840
# define screen_height 770
# define asteroid_number 4
# define bullet_number 500
# define boulder_number 7
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
struct space_boulders
{
	double x=-70,y=-70;
	int health=90;
	bool alive=false;
};
struct high_scores{
	char name[30];
	int score;
	char score_text[30];
};
struct ENEMY{
	double x,y;
	bool vertical=true;
	bool alive=false;
	double dx=5,dy=5;
	double health=100;
	int e_cnt=0;
	double bullet_x[500],bullet_y[500];
	bool bullet_show[500];
};

double space_x=370;
double space_y=0;

int space_health=150;
double health_x=650;
double health_y=710; 

int world=0;
int cnt=0;

asteroids asteroid[asteroid_number];
f_bullet own_bullet[bullet_number];
space_boulders space_boulder[boulder_number];
high_scores players[5];
ENEMY enemy[2];
FILE *fp;

int score=0;
double score_x=650;
double score_y=740;

double collision_x,collision_y;
bool collision_check=false;
int col_cnt=0;

double collsion2_x,collision2_y;
bool collision2_check=false;
int col2_cnt=0;

int page_state=0;
bool music_on=true;
bool gmusic_on=true;
bool pause=false;
bool boulder_active=false;

double healbox_x,healbox_y;
bool healbox_active=false;

double shield_x,shield_y,shieldbox_x,shieldbox_y;
bool shield_active=false,shieldbox_show=false;
int shield_hp=100;

double laser_x,laser_y;
double laser_state_x=650,laser_state_y=680;
bool laser_active=false,laser_usable=false;
int laser_cnt=0,laser_hp=0;
char laser_status[30]="Laser: Not Ready";

char lobby_sound[30]="sounds\\lobby.wav";
char game_sound[30]="sounds\\In game.wav";

char img[6][30]={"images\\home.bmp","images\\gamebg.bmp","images\\highscorebg.bmp","images\\home.bmp","images\\home.bmp","images\\gamebg2.bmp"};
char play[30]="images\\play.bmp";
char world1[30]="images\\world1.bmp";
char world2[30]="images\\world2.bmp";
char arenatitle[30]="images\\arenatitle.bmp";
char high_score[30]="images\\high_score.bmp";
char settings[30]="images\\settings.bmp";
char instructions[30]="images\\instructions.bmp";
char quit[30]="images\\quit.bmp";
char title[30]="images\\title.bmp";
char back[30]="images\\return.bmp";
char h_title[30]="images\\hTitle.bmp";
char s_title[30]="images\\sTitle.bmp";
char i_title[30]="images\\iTitle.bmp";
char control[30]="images\\controls.bmp";
char l_music[30]="images\\lobbymusic.bmp";
char g_music[30]="images\\gamemusic.bmp";
char volume[30]="images\\volume.bmp";
char mute[30]="images\\mute.bmp";
char spaceship[2][30]={"images\\spaceship.bmp","images\\spaceship2.bmp"};
char enemyship[2][30]={"images\\enemyship.bmp","images\\enemyship2.bmp"};
char asteroid_image[2][30]={"images\\asteroid.bmp","images\\asteroid2.bmp"};
char boulder[2][30]={"images\\boulder.bmp","images\\boulder2.bmp"};
char my_bullet[30]="images\\sbullet.bmp";
char collision[30]="images\\collision.bmp";
char collision2[30]="images\\collision2.bmp";
char healbox[30]="images\\health.bmp";
char shield[30]="images\\shield.bmp";
char laser[2][30]={"images\\laser.bmp","images\\laser2.bmp"};
char enemybullet[30]="images\\enemybullet.bmp";
char gameover[30]="images\\gameover.bmp";

char score_text[30]="Score: 0";
char score_show[30]="You Scored: 0";
char health[30]="Health: 150";

char tmp_name[1000];
int index=0;


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
				if(asteroid[i].x<40)asteroid[i].x=40;
				asteroid[i].y=screen_height+rand()%200;
				asteroid[i].alive=true;
			}
			//printf("Position of %d: %lf %lf\n",i,asteroid[i].x,asteroid[i].y);
		}
			
	}
}
void asteroid_show()
{
	int i;
	for(i=0;i<asteroid_number;i++){
		if(asteroid[i].alive){
			iShowBMP2(asteroid[i].x,asteroid[i].y,asteroid_image[world],0);
		}
	}
	//asteroid_change();
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
void bulletshow()
{
	int i;
	for(i=1;i<bullet_number;i++){
		if(own_bullet[i].bullet_show){
			iShowBMP2(own_bullet[i].x,own_bullet[i].y,my_bullet,0);
		}
	}
	//bullet_change();
}
void enemyship_show()
{
	int i;
	for(i=0;i<2;i++){
		if(enemy[i].alive){
			iShowBMP2(enemy[i].x,enemy[i].y,enemyship[world],0);
		}
	}
}
void boulder_change()
{
	int i;
	if(page_state==1 && !pause && boulder_active){
		for(i=0;i<7;i++){
			if(space_boulder[i].alive){
				space_boulder[i].y-=6;
				if(space_boulder[i].y<=-60){
					space_boulder[i].x=rand()%780;
					if(space_boulder[i].x<60)space_boulder[i].x=60;
					space_boulder[i].y=screen_height+rand()%600;
				}
			}
			else{
				space_boulder[i].x=rand()%780;
				if(space_boulder[i].x<60)space_boulder[i].x=60;
				space_boulder[i].y=screen_height+rand()%600;
				space_boulder[i].alive=true;
				space_boulder[i].health=90;
			}
		}
	}

}
void boulder_show()
{
	int i;
	for(i=0;i<boulder_number;i++){
		if(space_boulder[i].alive){
			iShowBMP2(space_boulder[i].x,space_boulder[i].y,boulder[world],0);
		}
	}
	//boulder_change();
}
void healbox_show()
{
	if(healbox_active){
		iShowBMP2(healbox_x,healbox_y,healbox,0);
	}
	
}
void healbox_change()
{
	if(page_state==1 && healbox_active && !pause){
		healbox_y-=5;
		if(healbox_y<=-30){
			healbox_active=false;
		}
		if((healbox_x+30 > space_x && healbox_x < space_x+90) && (healbox_y+30 > space_y && healbox_y < space_y+90)){
			healbox_active=false;
			healbox_y=-30;
			space_health+=15;
			if(space_health>150)space_health=150;
			sprintf(health,"Health: %d",space_health);
		}
	}
}
void shield_change(){
	if(page_state == 1 && shield_active && !pause){
		shield_y-=5;
		if(shield_y<=-30){
			shield_active=false;
		}
		if((shield_x+30 > space_x && shield_x < space_x+90) && (shield_y+30 > space_y && shield_y < space_y+90)){
			shield_active=false;
			shield_y=-30;
			shieldbox_show=true;
			shieldbox_x=space_x+45;
			shieldbox_y=45;
			shield_hp=100;
		}
	}
}
void shieldbox_change()
{
	if(page_state == 1 && !pause && shieldbox_show){
		shieldbox_x=space_x+45;
		shieldbox_y=45;
		shield_hp--;
		if(shield_hp<=0){
			shieldbox_show=false;
		}
	}
}
void laser_change()
{
	if(page_state==1 && !pause && laser_active){
		laser_x=space_x+35;
		laser_hp--;
		if(laser_hp<=0){
			laser_active=false;
			laser_usable=false;
			sprintf(laser_status,"Laser: Not Ready");
		}
	}
	if(page_state==1 && !pause && !laser_active){
		if(laser_hp>=200){
			laser_usable=true;
			sprintf(laser_status,"Laser: Ready");
		}
		else 
			laser_hp++;
	}
}
void shield_show(){
	if(shield_active){
		iShowBMP2(shield_x,shield_y,shield,0);
	}
}
void shieldboxx_show(){
	if(shieldbox_show){
		iSetColor(0,255,0);
		iCircle(shieldbox_x,shieldbox_y,50);
	}
}
void laser_show(){
	if(laser_active && laser_cnt%10!=0){
		iShowBMP2(laser_x,laser_y,laser[world],0);
	}
	laser_cnt++;
}
void enemybulletshow()
{
	int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<500;j++){
			if(enemy[i].bullet_show[j]){
				iShowBMP2(enemy[i].bullet_x[j],enemy[i].bullet_y[j],enemybullet,0);
			}
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
		iSetColor(0,0,0);
		iText(200,20,"Developed by: Shashwoto Chowdhury  Supervised by: Md. Masum Mushfiq",GLUT_BITMAP_HELVETICA_12);

	}
	if(page_state==-2){
		iShowBMP(0,0,img[0]);
		iShowBMP2(0,624,arenatitle,0);
		iSetColor(255,255,255);
		iText(115,535,"Into THE DARKNESS",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(50,245,world1);
		iText(495,535,"CARTOON WORLD",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(445,245,world2);
		iShowBMP2(212.5,50,back,0);
	}
	if(page_state==1){
		if(world==0)iShowBMP(0,0,img[page_state]);
		else iShowBMP(0,0,img[5]);
		iShowBMP2(space_x,space_y,spaceship[world],0);
		iSetColor(44,166,43);
		iText(score_x,score_y,score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,255,255);
		iText(health_x,health_y,health,GLUT_BITMAP_TIMES_ROMAN_24);
		asteroid_show();
		bulletshow();
		boulder_show();
		healbox_show();
		laser_show();
		enemyship_show();
		enemybulletshow();
		shield_show();
		shieldboxx_show();
		if(laser_usable){
			iSetColor(38,150,40);
			iText(laser_state_x,laser_state_y,laser_status,GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(!laser_usable){
			iSetColor(255,0,0);
			iText(laser_state_x,laser_state_y,laser_status,GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if(collision_check){
			iShowBMP2(collision_x,collision_y,collision,0);
			col_cnt++;
			if(col_cnt==10){
				collision_check=false;
				col_cnt=0;
			}
		}
		if(collision2_check){
			iShowBMP2(collsion2_x,collision2_y,collision2,0);
			col2_cnt++;
			if(col2_cnt==10){
				collision2_check=false;
				col2_cnt=0;
			}
		}
	}
	if(page_state==2){
		iShowBMP(0,0,img[page_state]);
		iShowBMP(0,624,h_title);
		//iSetColor(54,162,208);
		//iFilledRectangle(80,250,700,300);
		iSetColor(0,0,0);
		iText(120,480,"1",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(200,480,players[0].name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(650,480,players[0].score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,420,"2",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(200,420,players[1].name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(650,420,players[1].score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,360,"3",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(200,360,players[2].name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(650,360,players[2].score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,300,"4",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(200,300,players[3].name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(650,300,players[3].score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,240,"5",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(200,240,players[4].name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(650,240,players[4].score_text,GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(212.5,50,back,0);
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

		iShowBMP2(212.5,50,back,0);
	}
	if(page_state==4){
		iShowBMP(0,0,img[page_state]);
		iShowBMP(0,624,i_title);
		iShowBMP(110,192,control);
		iShowBMP2(212.5,50,back,0);
		
	}
	if(page_state==-1){
		iShowBMP(0,0,gameover);
		iSetColor(255,255,255);
		iText(350,470,score_show,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0,0,0);
		iText(286,250,tmp_name,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	//iText(40, 40, "Hi, I am iGraphics");
}


void iMouseMove(int mx, int my) {
	
	//place your codes here
}


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
		if(asteroid[i].x<40)asteroid[i].x=40;
		asteroid[i].y=screen_height+rand()%200;
		asteroid[i].alive=true;
	}
}
void boulder_initialize()
{
	int i;
	for(i=0;i<boulder_number;i++){
		space_boulder[i].x=rand()%780;
		if(space_boulder[i].x<60)space_boulder[i].x=60;
		space_boulder[i].y=screen_height+rand()%600;
		space_boulder[i].health=90;
		space_boulder[i].alive=true;
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
void boulder_clear()
{
	int i;
	boulder_active=false;
	for(i=0;i<boulder_number;i++){
		//space_boulder[i].x=-70;
		space_boulder[i].y=-70;
		space_boulder[i].health=90;
		space_boulder[i].alive=false;
	}
}
void enemyship_clear()
{
	int i;
	for(i=0;i<2;i++){
		enemy[i].x=0;
		enemy[i].y=-200;
		enemy[i].alive=false;
		enemy[i].vertical=true;
		enemy[i].dx=5;
		enemy[i].dy=5;
		enemy[i].health=100;
	}
}
void enemybullet_clear()
{
	int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<500;j++){
			enemy[i].bullet_x[j]=0;
			enemy[i].bullet_y[j]=-1000;
			enemy[i].bullet_show[j]=false;
		}
	}
}
void health_init()
{
	space_health=150;
	sprintf(health,"Health: %d",space_health);
}
void shield_clear()
{
	shield_active=false;
	shieldbox_show=false;
	shield_hp=100;
	shield_y=-30;
}
void iMouse(int button, int state, int mx, int my) {
	if(page_state==0){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=30&&my<=130){
			exit(0);
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=510&&my<=610){
			page_state=-2;
		}

		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=390&&my<=490){
			page_state=2;
			fp=fopen("score.txt","r");
			for(int i=0;i<5;i++){
				fscanf(fp,"%s %d",players[i].name,&players[i].score);
				sprintf(players[i].score_text,"%d",players[i].score);
			}
			fclose(fp);
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=270&&my<=370){
			page_state=3;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=235&&mx<=605&&my>=150&&my<=250){
			page_state=4;
		}
	}
	if(page_state==-2){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=50&&mx<=395&&my>=262&&my<=524){
			page_state=1;
			world=0;
			asteroid_initialize();
			if(gmusic_on){
				PlaySound(game_sound, NULL , SND_LOOP|SND_ASYNC);
			}
			else{
			 	PlaySound(0,0,0);
			}
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=445 && mx<=790 &&my>=262&&my<=524){
			page_state=1;
			world=1;
			asteroid_initialize();
			if(gmusic_on){
				PlaySound(game_sound, NULL , SND_LOOP|SND_ASYNC);
			}
			else{
			 	PlaySound(0,0,0);
			}
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=212.5&&mx<=627.5&&my>=50&&my<=150){
			page_state=0;
		}
	}
	if(page_state==1){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(!pause && !laser_active)bullet_initialize();
		}
	}
	if(page_state==2){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=212.5&&mx<=627.5&&my>=50&&my<=150){
			page_state=0;
		}
	}
	if(page_state==3){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=212.5&&mx<=627.5&&my>=50&&my<=150){
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
	if(page_state==4){
	 	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=212.5&&mx<=627.5&&my>=50&&my<=150){
			page_state=0;
		}
	}
	if(page_state == -1){
		int i;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=375&&mx<=610&&my>=137&&my<=205){
			fp=fopen("score.txt","r");
			for(i=0;i<5;i++){
				fscanf(fp,"%s %d",players[i].name,&players[i].score);
				//sprintf(players[i].score_text,"%d",players[i].score);
			}
			fclose(fp);
			fp=fopen("score.txt","w");
			printf("DEBUG: %s %d\n", tmp_name,score);
			for(i=0;i<5;i++){
				if(score>players[i].score){
					int j;
					printf("Debug: %d\n",i);
					for(j=4;j>i;j--){
						players[j].score=players[j-1].score;
						strcpy(players[j].name,players[j-1].name);
					}
					players[i].score=score;
					if(strlen(tmp_name)==0)strcpy(players[i].name,"Player");
					else strcpy(players[i].name,tmp_name);
					//sprintf(players[i].score_text,"%d",players[i].score);
					break;
				}
			}
			for(i=0;i<5;i++){
				printf("%s %d\n",players[i].name,players[i].score);
				fprintf(fp,"%s %d\n",players[i].name,players[i].score);
			}
			fclose(fp);
			tmp_name[0]='\0';
			bullet_clear();
			asteroid_clear();
			score_clear();
			health_init();
			laser_active=false;
			laser_usable=false;
			laser_hp=0;
			sprintf(laser_status,"Laser: Not Ready");
			boulder_clear();
			space_x=370;
			space_y=0;
			enemyship_clear();
			enemybullet_clear();
			shield_clear();
			healbox_active=false;
			page_state=0;
			index=0;
		}

	}

}

void iKeyboard(unsigned char key) {
	// if (key == 'q') {
	// 	exit(0);
	// }
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
		if(key == 'q'){
			sprintf(score_show,"You Scored: %d",score);
			page_state=-1;
			cnt=0;
			if(music_on){
				PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
			}
			else{
				PlaySound(0,0,0);
			}
		}
		if(key == 'p'){
			if(pause){
				pause=false;
			}
			else{
				pause=true;
			}
		}
		if(key == 'e'){
			if(!laser_active && laser_usable){
				laser_x=space_x+35;
				laser_y=90;
				laser_active=true;
			}
			else if(laser_active){
				laser_active=false;
				laser_cnt=0;
			}
		}
	}
	if(page_state == -1){
		if(index==0 && key == 'q'){

		}
		else{
			if(key != '\b'){
				tmp_name[index]=key;
				index++;
				tmp_name[index]='\0';
			}
			else{
				if(index>0){
					index--;
					tmp_name[index]='\0';
				}
			}
		}
	}
	
	//place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key) {
	if(page_state == 1){
		if(key == GLUT_KEY_LEFT){
			if(!pause){
				space_x-=5;
				if(space_x<=0){
					space_x=0;
				}
			}
		}
		if(key == GLUT_KEY_RIGHT){
			if(!pause){
				space_x+=5;
				if(space_x>=(screen_width-90)){
					space_x=screen_width-90;
				}
			}
		}
	}
}
void enemyship_init()
{
	int i;
	if(rand()%3==0 && page_state==1 && !pause){
		printf("Hello\n");
		for(i=0;i<2;i++){
			if(!enemy[i].alive){
				enemy[i].x=rand()%730;
				if(enemy[i].x<90)enemy[i].x=90;
				enemy[i].y=screen_height+rand()%200;
				enemy[i].alive=true;
				enemy[i].vertical=true;
				enemy[i].health=100;
			}
		}
	}
}
void enemy_bullet_initialize()
{
	int i,j;
	if(page_state==1 && !pause){
		for(i=0;i<2;i++){
			if(enemy[i].x + 20>=space_x && enemy[i].x<=space_x+20 && enemy[i].alive){
				if(!enemy[i].bullet_show[enemy[i].e_cnt]){
					enemy[i].bullet_x[enemy[i].e_cnt]=enemy[i].x+45;
					enemy[i].bullet_y[enemy[i].e_cnt]=enemy[i].y;
					enemy[i].bullet_show[enemy[i].e_cnt]=true;
					enemy[i].e_cnt++;
				}
				if(enemy[i].e_cnt>=500)enemy[i].e_cnt=0;
			}
		}
	}
	
}
void enemy_bullet_change()
{
	int i,j;
	if(page_state==1 && !pause){
		for(i=0;i<2;i++){
			for(j=0;j<500;j++){
				if(enemy[i].bullet_show[j]){
					enemy[i].bullet_y[j]-=5;
					if(enemy[i].bullet_y[j]<=0){
						enemy[i].bullet_show[j]=false;
						enemy[i].bullet_y[j]=-20;
					}
				}
			}
		}
	}

}
void enemyship_change()
{
	int i;
	if(page_state==1 && !pause){
		for(i=0;i<2;i++){
			if(enemy[i].alive){
				if(enemy[i].vertical){
					enemy[i].y-=enemy[i].dy;
					if(enemy[i].y<=650){
						enemy[i].vertical=false;
					}
				}
				else{
					if(enemy[i].x+20 >= space_x && enemy[i].x<=space_x+20){
						//enemy_bullet_initialize(i);
					}
					else{
						enemy[i].x-=enemy[i].dx;
						if(enemy[i].x<=0 || enemy[i].x>=840-90){
							enemy[i].dx*=(-1);
						}
					}
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
						score+=5;
						if(score>=200 && !boulder_active){
							boulder_initialize();
							boulder_active=true;
						}
						sprintf(score_text,"Score: %d",score);
						break;
					}
				}
			}
		}
	}
}

void boulder_collision_check()
{
	int i,j;
	if(page_state==1 && !pause){
		for(i=1;i<bullet_number;i++){
			if(own_bullet[i].bullet_show){
				for(j=0;j<7;j++){
					if((own_bullet[i].x+10 > space_boulder[j].x && own_bullet[i].x < space_boulder[j].x+60) && (own_bullet[i].y+15 > space_boulder[j].y && own_bullet[i].y < space_boulder[j].y+60)){
						own_bullet[i].bullet_show=false;
						own_bullet[i].y=-20;	
						space_boulder[j].health-=30;
						if(space_boulder[j].health<=0){
							space_boulder[j].alive=false;
							collision2_check=true;
							collsion2_x=space_boulder[j].x;
							collision2_y=space_boulder[j].y;
							score+=10;
							sprintf(score_text,"Score: %d",score);
						}
						else{
							collision_check=true;
							collision_x=space_boulder[j].x;
							collision_y=space_boulder[j].y;
						}
						break;
					}
				}
			}
		}
	}
}

void spaceship_asteroid_collision()
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
				if(!shieldbox_show)space_health-=5;
				if(space_health<=0){
					sprintf(score_show,"You Scored: %d",score);
					page_state=-1;
					cnt=0;
					if(music_on){
						PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
					}
					else{
						PlaySound(0,0,0);
					}
				}
				else 
					sprintf(health,"Health: %d",space_health);
				break;
			}
		}
	}
}
void enemyspaceship_collision()
{
	int i,j;
	if(page_state==1 && !pause){
		for(i=0;i<bullet_number;i++){
			if(own_bullet[i].bullet_show){
				for(j=0;j<2;j++){
					if((own_bullet[i].x+10 > enemy[j].x && own_bullet[i].x < enemy[j].x+90) && (own_bullet[i].y+15 > enemy[j].y && own_bullet[i].y < enemy[j].y+90)){
						own_bullet[i].bullet_show=false;
						own_bullet[i].y=-20;
						enemy[j].health-=20;
						if(enemy[j].health<=0){
							enemy[j].alive=false;
							score+=20;
							sprintf(score_text,"Score: %d",score);
							collision2_check=true;
							collsion2_x=enemy[j].x;
							collision2_y=enemy[j].y;
							enemy[j].y=-200;
						}
						else{
							collision_check=true;
							collision_x=enemy[j].x;
							collision_y=enemy[j].y;
						}
						break;
					}
				}
			}
		}
	}
}
void spaceship_boulder_collision()
{
	int i;
	if(page_state==1 && !pause){
		for(i=0;i<7;i++){
			if((space_boulder[i].x+60 > space_x && space_boulder[i].x < space_x+90) && (space_boulder[i].y+60 > space_y && space_boulder[i].y < space_y+90)){
				space_boulder[i].alive=false;
				collision2_check=true;
				collsion2_x=space_boulder[i].x;
				collision2_y=space_boulder[i].y;
				if(!shieldbox_show)space_health-=10;
				if(space_health<=0){
					sprintf(score_show,"You Scored: %d",score);
					page_state=-1;
					cnt=0;
					if(music_on){
						PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
					}
					else{
						PlaySound(0,0,0);
					}
				}
				else
					sprintf(health,"Health: %d",space_health);
				break;
			}
			//printf("Position of %d: %lf %lf\n",i,space_boulder[i].x,space_boulder[i].y);
		}
	}
}
void enemybullet_spaceship_collision()
{
	int i;
	if(page_state==1 && !pause){
		for(i=0;i<2;i++){
			for(int j=0;j<500;j++){
				if(enemy[i].bullet_show[j]){
					if((enemy[i].bullet_x[j]+10 > space_x && enemy[i].bullet_x[j] < space_x+90) && (enemy[i].bullet_y[j]+15 > space_y && enemy[i].bullet_y[j] < space_y+90)){
						enemy[i].bullet_show[j]=false;
						collision_check=true;
						collision_x=enemy[i].bullet_x[j];
						collision_y=enemy[i].bullet_y[j];
						enemy[i].bullet_y[j]=-1000;
						if(!shieldbox_show)space_health-=10;
						if(space_health<=0){
							sprintf(score_show,"You Scored: %d",score);
							page_state=-1;
							cnt=0;
							if(music_on){
								PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
							}
							else{
								PlaySound(0,0,0);
							}
						}
						else
							sprintf(health,"Health: %d",space_health);
					}
				}
			}
		}
	}
}
void laser_collision()
{
	int i;
	if(page_state==1 && !pause && laser_active){
		for(i=0;i<asteroid_number;i++){
			if((laser_x+20 > asteroid[i].x && laser_x < asteroid[i].x+40) && (laser_y+670 > asteroid[i].y && laser_y < asteroid[i].y+40)){
				asteroid[i].alive=false;
				asteroid[i].dx=5;
				asteroid[i].dy=5;
				asteroid[i].in=false;
				collision_x=asteroid[i].x;
				collision_y=asteroid[i].y;
				collision_check=true;
				score+=5;
				if(score>=200 && !boulder_active){
					boulder_initialize();
					boulder_active=true;
				}
				sprintf(score_text,"Score: %d",score);
				break;
			} 
		}
		if(boulder_active){
			for(i=0;i<boulder_number;i++){
				if((laser_x+20 > space_boulder[i].x && laser_x < space_boulder[i].x+60) && (laser_y+670 > space_boulder[i].y && laser_y < space_boulder[i].y+60)){
					space_boulder[i].health-=45;
					if(space_boulder[i].health<=0){
						space_boulder[i].alive=false;
						collision2_check=true;
						collsion2_x=space_boulder[i].x;
						collision2_y=space_boulder[i].y;
						score+=10;
						sprintf(score_text,"Score: %d",score);
					}
					else{
						collision_check=true;
						collision_x=space_boulder[i].x;
						collision_y=space_boulder[i].y;
					}
					break;
				}
			}
		}
		for(i=0;i<2;i++){
			if((laser_x+20 > enemy[i].x && laser_x < enemy[i].x+90) && (laser_y+670 > enemy[i].y && laser_y < enemy[i].y+90)){
				enemy[i].health-=20;
				if(enemy[i].health<=0){
					enemy[i].alive=false;
					score+=20;
					sprintf(score_text,"Score: %d",score);
					collision2_check=true;
					collsion2_x=enemy[i].x;
					collision2_y=enemy[i].y;
					enemy[i].y=-200;
				}
				else{
					collision_check=true;
					collision_x=enemy[i].x;
					collision_y=enemy[i].y;
				}
				break;
			}
		}
	}
}
void change()
{
	asteroid_change();
	bullet_change();
	boulder_change();
	healbox_change();
	laser_change();
	enemyship_change();
	enemy_bullet_change();
	shield_change();
	shieldbox_change();
}
void collisions()
{
	asteroid_collision_check();
	boulder_collision_check();
	spaceship_asteroid_collision();
	spaceship_boulder_collision();
	enemyspaceship_collision();
	enemybullet_spaceship_collision();
	laser_collision();
}
void healbox_init()
{
	if(space_health<=75 && !healbox_active){
		healbox_active=true;
		healbox_x=rand()%800;
		if(healbox_x<30)healbox_x=30;
		healbox_y=screen_height+rand()%200;
	}
}
void shield_init()
{
	if(rand()%5==0 && page_state == 1 && !pause && !shield_active && !shieldbox_show){
		shield_active=true;
		shield_x=rand()%800;
		if(shield_x<30)shield_x=30;
		shield_y=screen_height+rand()%200;
	}
}

int main() {
	srand(time(0));
	iSetTimer(25,change);
	// iSetTimer(25,asteroid_collision_check);
	// iSetTimer(25,boulder_collision_check);
	// iSetTimer(25,spaceship_asteroid_collision);
	// iSetTimer(25,spaceship_boulder_collision);
	// iSetTimer(25,laser_collision);
	iSetTimer(25,collisions);
	iSetTimer(10000,healbox_init);
	iSetTimer(5000,shield_init);
	iSetTimer(5000,enemyship_init);
	iSetTimer(250,enemy_bullet_initialize);
	if(music_on){
		PlaySound(lobby_sound, NULL , SND_LOOP|SND_ASYNC);
	}
	
	iInitialize(screen_width, screen_height, "Asteroid Game");
	//place your own initialization codes here.
	return 0;
}
