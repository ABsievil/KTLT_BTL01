#include "knight.h"
// 
//khai báo hàm
void display(int,int,int,int,int,int);
void adventureToKoopa(string,int &,int &,int &,int &,int &,int &);
float baseDamage(int);

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {  //in các giá trị khi game end.
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

float baseDamage(int loaidoithu){          //trả về baseDamage
   if(loaidoithu==1) return 1.0;
   else if(loaidoithu==2) return 1.5;
   else if(loaidoithu==3) return 4.5;
   else if(loaidoithu==4) return 7.5;
   else if(loaidoithu==5) return 9.5;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    #define N 256 
    FILE * fp=NULL;
    char line[N];  int sukien[7]; int trangthaitihon; //trangthaitihon chính là sự kiện thứ i được gán vào khi hiệp sĩ biến thành trangthaitihon
    rescue= -1;

    fp=fopen("tc1_input","r"); 

    //lấy giá trị của 2 hàng trong file
    fgets(line, N, fp);
    sscanf(line,"%d %d %d %d %d", &HP, &level, &remedy, &maidenkiss, &phoenixdown);  
    fgets(line, N, fp);
    sscanf(line,"%d %d %d %d %d %d", &sukien[1],&sukien[2],&sukien[3],&sukien[4],&sukien[5],&sukien[6]);
    int MaxHP=HP;
    for(int i=0;i<=6;i++){if(sukien[i]>19) sukien[i]=0;
    }

    for(int i=1;i<7;i++){
         int b = i%10;
         int levelO = i > 6?(b > 5?b : 5) : b; 

         if(sukien[i]==0) {rescue=1;break;}   //nếu gặp sự kiện =0 thì thoát ra và hoàn thành chương trình
         else if(sukien[i]==6){     //gặp Shaman
              if(level>levelO) {   //truyền sukien[i] vào biến loaidoithu
               if(level<9)  level+=2;  
              }
              else if(level<levelO){
                HP=HP<5?1:(HP/5) ; 
                if(remedy>0)
                {  
                  remedy--;  //nếu có thuốc remedy thì ko biến thành trạng thái tí hon
                  HP*=5;
                }
                else trangthaitihon=i; 
              }
              else continue;
         }
         else {       //  các sự kiện còn lại
            if(level>levelO) {   //truyền sukien[i] vào biến loaidoithu
               if(level<10)  level++;  
            }
            else if(level<levelO) {
                int damage = baseDamage(sukien[i])*levelO*10;
                HP-=damage;
            }
            else continue;
            if(i>=trangthaitihon+3){
                HP*=5;
                HP= HP>MaxHP?MaxHP:HP;   //nếu HP lớn hơn HP ban đầu thì giảm về HP ban đầu
            }
         }

         

          if(HP<=0) {             //check HP sau mỗi vòng
            if(phoenixdown>0){
                phoenixdown--;
                HP=MaxHP;
                trangthaitihon=10;
            }
            else {rescue=0;break;}
          } 
    }
    display(HP,level,remedy,maidenkiss,phoenixdown,rescue);

}