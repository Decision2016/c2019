#include<cstdio>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<windows.h>

#define W 160
#define H 40

void Gotoxy(int posx,int posy);
int dirx[4] = {-1,0,1,0};
int diry[4] = {0,-1,0,1};
int start_w,start_h,pos; 
int grades[10];
std::string Menu[6] = {"Welcome to PushBoxes Game!","You can use WASD to move.","Press [ 1 ] to start game.","Press [ 2 ] to chose level.",
                       "Press [ 3 ] to see previous grade.","Press [ 4 ] to exit game"};
std::string EditHelper[8] = {"Ohhhhhhhhh,you find it!","This place can edit maps.","Press the level number you want to edit to press.",
                            "Remember to keep boxes number and targets number is equality!","You can use [ + ] and [ - ] to contral blocks."
							"Press [ B ] to put a Box,and press [ T ] to put a target.","And you can also press [ P ] to chose player's pos.",
							"If you want to restore,press [ R ]","Press [ ESC ] to return."};
std::string ErrorInfor[2] = {"The map data is wrong.","It would return after 3 seconds..."};
std::string Congratulation[3] = {" ","Press N to Next level.","Press [ ESC ] to return menu."};
std::string con[2] = {"You use "," step solve this level."};

/*<---------------------------------�Զ���������� --------------------------------->*/ 

//����һ��Box�࣬�������ӵ��ƶ��Ȳ��� 							
class Box{                              
private:
    int x,y;    
public:
    void Init(int posx,int posy){
    	x = posx;
    	y = posy;
    }
    
    int X(){
    	return x;
    }
    
    int Y(){
    	return y;
    }
    
    void Change(int posx,int posy){
    	x = posx;
    	y = posy;
    }
};

//����һ��player�࣬������ҵ��ƶ����������������λ�� 
class Player{                         
private:
    int x,y;
public:
    void init(int posx,int posy){
    	x = posx;
    	y = posy;
    }
    
    //����ƶ� 	
    bool Moveto(int toX,int toY,int w,int h){             
    	if(toX<0||toX>h||toY<0||toY>w) return false;
    	Gotoxy(x,y);
    	std::cout<<" ";
    	x = toX;
    	y = toY;
    	Gotoxy(x,y);
    	std::cout<<"\033[1m\033[31m"<<"@";
    	return true;
    }
    
    int X(){
    	return x;
    }
    
    int Y(){
    	return y;
    }
    
    //�ڿ���̨����ʾ 
    void Show(int h){                             
        Gotoxy(x,y);
	    std::cout<<"\033[1m\033[31m"<<"@"<<std::endl;
	    Gotoxy(h + 1,0);
	}
};

//����һ��MazeMap�࣬������Ϸ����Ҫ��������ҵ��ƶ������ӵ��жϵ� 
class MazeMap{                                
private:
	int Map[50][50];
	int px,py;
	int BoxNum,TarNum;
	std::vector<Box> Boxes;
public:
	int w,h;
	
	//�ֲ�ˢ�µ�ͼ�ڿ���̨��λ�ã�edit=1��ʱ���ʾ�༭ģʽ 
	void Refresh(int posx,int posy,int edit){                
		Gotoxy(posx,posy);
		switch(Map[posx][posy]){
			case(0):
			    std::cout<<" ";
			    break;
            case(1):
                std::cout<<"\033[1m\033[32m"<<"#";
                break;
            case(2):
                std::cout<<"\033[1m\033[33m"<<"O";
                break;
            case(3):
                std::cout<<"\033[1m\033[34m"<<"X";
                break;
            case(4):
                if(edit){
				    std::cout<<"P";
                }
                break;
		}
		Gotoxy(h+1,0);
	}  
	
	//�����￪ʼ�Ǳ༭��һЩ���� 
	void BreakBlock(Player *t){                                
		Map[t->X()][t->Y()] = 0;
	}
	
	void AddBlock(Player *t){
		Map[t->X()][t->Y()] = 1;
	}
	
	void SetBoxPos(Player *t){
		Map[t->X()][t->Y()] = 2;
	}
	
	void SetTarPos(Player *t){
		Map[t->X()][t->Y()] = 3;
	}
	
	void ChangePos(Player *t){
		Map[t->X()][t->Y()] = 4;
		Map[px][py] = 0;
		Refresh(px,py,1);
		px = t->X();
		py = t->Y();
	}
	
	//���ó�ʼλ�õȲ�������ӿ� 
	void Set(int width,int higth){
		w = width;
		h = higth;
	}
	
	void preInit(int posx,int posy,int value,bool edit){
		Map[posx][posy] = value;
		if(value == 4){
			px = posy;
			py = posx;
		}
		else if(value == 2&&!edit){
			Box t;
			Map[posx][posy] = 0;
			t.Init(posx,posy);
			Boxes.push_back(t);
		}
	}
	
	void SetPlayerPos(Player* t){
		t->init(px,py);
	}
	
	//�ļ����ʱ���� 
	int Output(int posx,int posy){
		return Map[posx][posy];
	}
	
	//�����ӵ��ƶ�����������ƶ��ɹ������� 
	bool MoveBox(int toX,int toY,Box* t){
		if(Map[toX][toY] == 0 || Map[toX][toY] == 3 || Map[toX][toY] == 4){
			Gotoxy(t->X(),t->Y());
			std::cout<<" ";
			Gotoxy(toX,toY);
			std::cout<<"\033[1m\033[33m"<<"O";
			Refresh(t->X(),t->Y(),0);
			t->Change(toX,toY);
			return true;
		}
		return false;
	}
	
	//����Ƿ����ƶ����жϣ�������Ӳ��ܶ�����ǰ����ǽ�ȣ����ؼ٣���ʾ�����ƶ� 
	bool canMove(int toX,int toY,int dir){
		int l = Boxes.size();
		for(int i = 0;i<l;i++){
			if(Boxes[i].X() == toX && Boxes[i].Y() == toY){
				if(MoveBox(toX + dirx[dir],toY + diry[dir],&Boxes[i])) return true;
				else return false;
			}
		}
		if(Map[toX][toY] == 0 || Map[toX][toY] == 3 || Map[toX][toY] == 4){
			return true;
		}
		else return false;
	}
	
	//����Ƿ������е����Ӷ��ڶ�Ӧλ�������� 
	bool CheckAllBox(){
		int l = Boxes.size();
		for(int i = 0;i<l;i++){
			if(Map[Boxes[i].X()][Boxes[i].Y()] == 3) continue;
			else return false;
		}
		return true;
	}
	
	//��ʾ�õ�ͼ��������� 
	void ShowBox(){
		int l = Boxes.size();
		for(int i = 0;i<l;i++){
			Gotoxy(Boxes[i].X(),Boxes[i].Y());
			std::cout<<"\033[1m\033[33m"<<"O";
		}
	}
	
	//��ӡ��ͼ 
	void Show(int edit){
		system("cls");
		for(int i = 0;i<=h;i++){
			for(int j = 0;j<=w;j++){
				if(Map[i][j] == 1) std::cout<<"\033[1m\033[32m"<<"#";
				else if(Map[i][j] == 2) std::cout<<"\033[1m\033[33m"<<"O";
				else if(Map[i][j] == 3) std::cout<<"\033[1m\033[34m"<<"X";
				else if(Map[i][j] == 4&&edit) std::cout<<"P";
				else std::cout<<" ";
			}
			std::cout<<std::endl;
		}
		ShowBox();
	}
	
	//���༭�Ƿ�Ϸ� 
	bool Check(){
		BoxNum = TarNum = 0;
		for(int i = 0;i<=h;i++){
			for(int j = 0;j<=w;j++){
				if(Map[i][j] == 2) BoxNum++;
				else if(Map[i][j] == 3) TarNum++;
			}
		}
		if(BoxNum == TarNum) return true;
		else return false;
	}
	
	bool Clear(){
		BoxNum = TarNum = 0;
		Boxes.clear();
	}
};

MazeMap Maps[10];
Player player;

//���ÿ���̨��С 
void preInit(){
	system("mode con cols=160 lines=40");
}

//���ļ������ͼ�����뵽MazeMap���飬edit = 1 ��ʾ�༭ģʽ 
void Mapinit(int edit){
	std::fstream mapfile("gamemap.dat",std::ios::in);
	std::fstream mapdata("mapdata.dat",std::ios::in);
	int w,h,t;
	for(int i = 1;i<10;i++){
		mapdata >> w >> h;
		Maps[i].Clear();
		Maps[i].Set(w,h);
		for(int j = 0;j<=h;j++){
			for(int k = 0;k<=w;k++){
				mapfile >> t;
				Maps[i].preInit(j,k,t,edit);
			}
		}
	}
	mapfile.close();
	mapdata.close();
}

//������ת��Ϊstring�� 
std::string to_string(int x){
	std::string t,res;
	while(x!=0){
		t.push_back('0' + x%10);
		x/=10;
	};
	for(int i = t.length() - 1;i>=0;i--){
		res.push_back(t[i]);
	}
	return res;
}

//��ӡ��Ϣ�ĺ����������ַ������� 
void PrintInformation(std::string* ss,int num){
    system("cls");
	int maxx = 0,len;
	for(int i = 0;i<num;i++){
		len = ss[i].length();
		maxx = std::max(len,maxx);
	}
	start_w = (W - maxx) / 2;
	start_h = (H - num*2) / 2;
	for(int i = 1;i<=H;i++){
		if(i == start_h){
			for(int k = 0;k<num;k++){
				int tmp = start_w + maxx+1;
				for(int l = 1;l<=W;l++){
					if(l==start_w - 2||l==tmp + 2) std::cout<<"\033[1m\033[31m"<<"#";
					else if(l==start_w+1) std::cout<<"\033[1m\033[31m"<<ss[k],l+=ss[k].length() - 1;
					else std::cout<<" ";
				}
				std::cout<<std::endl;
				for(int l = 1;l<=W;l++){
					if(l==start_w - 2||l==tmp + 2) std::cout<<"\033[1m\033[31m"<<"#";
					else std::cout<<" ";
				}
				std::cout<<std::endl;
			}
			i+=2*num;
		}
		else if(i == start_h + 2*num + 1 || i == start_h-1){
			for(int j = 1;j<=W;j++){
				if(j>=start_w - 2&&j<=start_w + maxx + 3) std::cout<<"\033[1m\033[31m"<<"#";
				else std::cout<<" ";
			}
			std::cout<<std::endl;
		}
		else std::cout<<std::endl;	
	}
}


//�ֲ�ˢ��ʹ�ã�������ƶ�����Ӧ��λ�� 
void Gotoxy(int posx,int posy){
	COORD CUR;
	HANDLE hout;
	CUR.X = posy;
	CUR.Y = posx;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,CUR);
}

//��ȡ��Ұ��µļ������ض�Ӧ��ֵ 
int GetTabs(){
	char c = getch();
	if(c == 27) return 10;
	char s[10] = {'w','a','s','d','t','b','p','=','-','r'};
	for(int i = 0;i<10;i++){
		if(s[i] == c) return i;
	}
	return -1;
}

//����ͼ���浽�ļ��У�������editģʽ��ʹ�õĺ��� 
void SaveMaps(){
	int th,tw;
	std::fstream mapfile("gamemap.dat",std::ios::in|std::ios::out|std::ios::trunc);
	for(int i = 1;i<10;i++){
		th = Maps[i].h;
		tw = Maps[i].w;
		for(int j = 0;j<=th;j++){
			for(int k = 0;k<=tw;k++){
				mapfile << Maps[i].Output(j,k) << " ";
			}
		}
		mapfile<<std::endl;
	}
	mapfile.close();
}

//�Ե�ͼ���б༭��һϵ�в��� 
void Edit(int x){
	int Command;
	Mapinit(1);
	Maps[x].Show(1);
	Maps[x].SetPlayerPos(&player);
	player.Show(Maps[x].h);
	while(1){
		Command = GetTabs();
		if(Command == -1) continue;
		if(Command < 4){
			int tx = player.X() + dirx[Command];
			int ty = player.Y() + diry[Command];
			if(player.Moveto(tx,ty,Maps[x].w,Maps[x].h))
			{
				tx -= dirx[Command];
		        ty -= diry[Command];
			    Maps[x].Refresh(tx,ty,1);
			    Gotoxy(Maps[x].h+ 1,0);
			}
		}
		else{
			switch(Command){
				case(4):
				    Maps[x].SetTarPos(&player);
				    break;
				case(5):
				    Maps[x].SetBoxPos(&player);
				    break;
				case(6):
				    Maps[x].ChangePos(&player);
				    break;
				case(7):
				    Maps[x].AddBlock(&player);
				    break;
                case(8):
                    Maps[x].BreakBlock(&player);
                    break;
                case(10):
                    {
                  	    if(Maps[x].Check()){
                    	    SaveMaps();
                    	    Mapinit(1);
                    	    return ;
                        }
                        else{
                    	    PrintInformation(ErrorInfor,2);
                    	    Mapinit(1);
                    	    Sleep(3000);
                    	    return ;
                        }
                    }
                    break;
			}
		}
		Sleep(125);
	}
}

//��ͼ�༭ 
void MapEdit(){
	int Command;
	while(1){
		PrintInformation(EditHelper,8);
		Command = getch();
		if(Command>='0' && Command <='9'){
			Edit(Command - '0');
		}
		else if(Command == 'r'){
            system("type basemap.dat > gamemap.dat");
            std::string s[1] = "Restore Successful!";
            std::cout<<s[0]<<std::endl;
            Sleep(1000);
		}
		else if(Command == 27){
			return ;
		}
	}
}

//���ļ��л�ȡ������������ 
void GetGrade(){
	std::fstream file("grade.dat",std::ios::in);
	for(int i = 1;i<10;i++){
		file >> grades[i];
	}
	file.close();
}

//����������ļ��� 
void SaveGrade(int x,int level){
	std::fstream file("grade.dat",std::ios::in|std::ios::out);
	GetGrade();
	if(grades[level] > x || grades[level] == 0){
		grades[level] = x;
	}
	for(int i = 1;i<10;i++){
		file << grades[i] << " ";
	}
	file.close();
}

//��ӡ���� 
void PrintGrade(){
	char c;
	GetGrade();
	for(int i = 1;i<10;i++){
		std::cout<<"Your highest grade in level "<<i<<" is "<<grades[i]<<"."<<std::endl;
	}
	c = getch();
	if(c == 27) return ;
}

//��Ϸ�����岿�֣�����level��ʾ��ǰ��Ĺؿ�������ֵλlevel+1��0
//����levelʱ������һ�أ������˵��˵��� 
int GameMain(int level){
	MazeMap Tmap = Maps[level];
	Tmap.SetPlayerPos(&player);
	Tmap.Show(0);
	player.Show(Tmap.h);
	int grade = 0;
	int Command;
	while(1){
		Command = GetTabs();
		int px,py,nx,ny,t;
		if(Command == 10) return 0;
		if(Command<0||Command>3) continue;
		px = player.X();
		py = player.Y();
		nx = px + dirx[Command];
		ny = py + diry[Command];
		t = Tmap.Output(nx,ny);
		if(Tmap.canMove(nx,ny,Command)){
			player.Moveto(nx,ny,Tmap.w,Tmap.h);
			Tmap.Refresh(px,py,0);
			Gotoxy(Tmap.h + 1,0);
			grade++;
		}
		if(Tmap.CheckAllBox()){
			std::string TempString = con[0] + to_string(grade) + con[1];
			Congratulation[0] = TempString;
			PrintInformation(Congratulation,3);
			SaveGrade(grade,level);
			Command = getch();
			if(Command == 'n'){
				if(level == 9) return 0;
				else return level + 1;
			}
			else if((int)Command == 27) return 0;
		}
	}
}
//��Ϸ�˵��Ĳ��� 
void GameMenu(){
    Mapinit(0);
    memset(grades,0,sizeof(grades));
    int level = 0;
    int Command;
    while(1){
    	PrintInformation(Menu,6);
    	Command = getch();
    	switch(Command){
	    	case('1'):
				{
					level = GameMain(1);
	    		    while(1){
    		    		if(level == 0) break;
    		    		else level= GameMain(level);
    		    	}   
	    	    }
	    	    break;
            case('2'):
                {
                	system("cls");
                	std::cout<<"Please input level you want to paly:";
                	std::cin>>level;
	    		    while(1){
    		    		if(level == 0) break;
    		    		else level = GameMain(level);
    		    	}
    		    	break;
                }
           case('3'):
               {
               	    system("cls");
               	    GetGrade();
               	    PrintGrade();
               }
               break;
           case('4'):
               return ;
	    }
	    if((int)Command == 13){
    		MapEdit();
    		Mapinit(0);
    	}
    }
}

int main(){
	preInit();
	GameMenu();
	return 0;
}
