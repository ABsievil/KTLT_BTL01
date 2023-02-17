#include "knight.h"
// 
//khai báo hàm
void display(int,int,int,int,int,int);
void adventureToKoopa(string,int &,int &,int &,int &,int &,int &);
float baseDamage(int);
void docsukien(char);
int set_HP(int,int,int);
//biến và mảng toàn cục:
 vector< int > sukien;


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

int set_HP(int level, int phoenixdown,int HP){
  int n1= ((level + phoenixdown)%5 + 1)*3;
  int s1=0;
  for(int i=0,j=99;i<=n1,j>10;i++,j-=2){
    s1+=j;
  }
  HP+=(s1%100);


while(1){
  int so_uoc_chung=0;
   for(int i=1;i<=HP;i++){
      if(HP%i==0) so_uoc_chung++;
   }
   if(so_uoc_chung>2) HP++;
   else break;
}
  return HP;
}

void docsukien(char line[]){   //đọc sự kiện ở hàng 2
   int index=0;
   while(line[index]!='\n'){
    if(index==0) {
      if(line[index+1]==' ' || line[index+1]=='\n') sukien.push_back(int(line[index] - '0'));
      else if(line[index+2]==' '|| line[index+2]=='\n') sukien.push_back(int(line[index] - '0')*10+int(line[index+1] - '0'));
    }
    else{
      if(line[index]!=' ' && line[index-1]==' '){
          if(line[index+1]==' ' || line[index+1]=='\n') sukien.push_back(int(line[index] - '0'));
          else if(line[index+2]==' ' || line[index+2]=='\n') sukien.push_back(int(line[index] - '0')*10+int(line[index+1] - '0')); 
      }
    }
    index++;
   }
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    #define N 256 
    FILE * fp=NULL;
    char line[N];  int trangthaitihon; //lưu giá trị i khi hiệp sĩ biến thành trangthaitihon
    rescue= -1;        int luu_level;int trangthaiech;  int trangthaiech1=0,trangthaitihon1=0;

    fp=fopen("tc1_input","r"); 
    //lấy giá trị của hàng 1 trong file
    fgets(line, N, fp);
    sscanf(line,"%d %d %d %d %d", &HP, &level, &remedy, &maidenkiss, &phoenixdown);
    //lấy giá trị của hàng 2 trong file  
    fgets(line, N, fp);
    docsukien(line);
    int MaxHP=HP;


    for(int i=0;i<sukien.size();i++){  cout<<"dang chay qua ma su kien thu "<<i+1<<endl;   // nhớ xóa hàng này
         int j=i+1;
         int b = j%10;
         int levelO = j > 6?(b > 5?b : 5) : b; 

         if(sukien[i]==0) {rescue=1;break;}   //nếu gặp sự kiện =0 thì thoát ra và hoàn thành chương trình

         else if(sukien[i]==7){
            if(j<trangthaitihon1) goto label;   //nếu đang ở trạng thái tí hon thì không thực hiện hàm
            if(level>levelO) { 
               if(level<9)  level+=2;  
              }
            else if(level<levelO){
              if(maidenkiss>=1){
                maidenkiss--;
              }            
              else {
                luu_level=level;
                level=0;
                trangthaiech=j;
                trangthaiech1=trangthaiech+3;
              }
            }  
        label:{}
         }
         else if(sukien[i]==6){     //gặp Shaman
         if(j<trangthaiech1) goto label2;
              if(level>levelO) {   
               if(level<9)  level+=2;  
              }
              else if(level<levelO){
                HP=HP<5?1:(HP/5) ; 
                if(remedy>0)
                {  
                  remedy--;  //nếu có thuốc remedy thì ko biến thành trạng thái tí hon
                  HP*=5;
                }
                else 
                {
                  trangthaitihon=j; 
                  trangthaitihon1=trangthaitihon+3;
                }
              }

         label2:{}     
         }
         
         else if(sukien[i]==11){  
           HP=set_HP(level,phoenixdown,HP);
           HP= HP>MaxHP?MaxHP:HP;
         }


         else {       //  các sự kiện còn lại
            if(level>levelO) {   //truyền sukien[i] vào biến loaidoithu
               if(level<10)  level++;  
            }
            else if(level<levelO) {
                int damage = baseDamage(sukien[i])*levelO*10;
                HP-=damage;
            }

            if(j>=trangthaitihon+3){
                HP*=5;
                HP= HP>MaxHP?MaxHP:HP;   //nếu HP lớn hơn HP ban đầu thì giảm về HP ban đầu
            }
            if(j>=trangthaiech+3){
              level=luu_level;
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
          if(HP>0 && i==sukien.size()-1) rescue=1;   //lưu lại giá trị rescue cho sự kiện cuối
      display(HP,level,remedy,maidenkiss,phoenixdown,rescue); // nhớ xóa hàng này
    }
    display(HP,level,remedy,maidenkiss,phoenixdown,rescue);

}