#include "knight.h"
#include <vector>
using namespace std;

//khai báo hàm
void display(int,int,int,int,int,int);
void adventureToKoopa(string,int &,int &,int &,int &,int &,int &);
float baseDamage(int);
void set_sukien(char);
void set_file_dulieuthem(char);
int set_HP(int,int,int);
int setHP_fibonaci(int);
int check_namma(int);
bool check_nui(vector<int> );
void findMaxiMini(vector <int>);
//biến và mảng toàn cục:
 vector< int > sukien;
vector< int > nammaMushGhost;
vector <int> chuoi_mush_ghost;
int maxi,mini,mtx=-2,mti=-3;


 // bug nhặt được thuốc tự động sử dụng khi trạng thái tí hon và ếch chưa build
 //bug nấm loại 1 chạy sai

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

int set_HP(int level, int phoenixdown,int HP){   //dùng setup cho mã sự kiện 11
  int n1= ((level + phoenixdown)%5 + 1)*3;
  int s1=0;
  for(int i=0,j=99;i<=n1,j>10;i++,j-=2){
    s1+=j;
  }
  HP+=(s1%100);
  int conHP=HP;

while(1){
  int so_uoc_chung=0;
   for(int i=1;i<=HP;i++){
      if(HP%i==0) so_uoc_chung++;
   }
   if(so_uoc_chung>2) HP++;   
   else if(so_uoc_chung==2 && HP==conHP) HP++;  //nếu HP là số nguyên tố thì tăng HP lên 1 để tìm snt gần HP nhất
   else if(so_uoc_chung==2 && HP!=conHP) break;  //nếu tìm được snt gần HP nhất rồi thì thoát while
}
  return HP;
}

int setHP_fibonaci(int HP) // hàm nhập giá trị HP và trả về giá trị HP mới bằng số Fibonacci gần nhất
{
    int f1 = 0, f2 = 1, f3 = 1;
    while (f3 < HP)
    {
        f1 = f2;
        f2 = f3;
        f3 = f1 + f2;
    }
    if (abs(HP - f2) <= abs(f3 - HP))
    {
        return f2;
    }
    else
    {
        return f3;
    }
}

bool check_nui(vector<int> arr) {
    int n = arr.size();
    // Tìm đỉnh núi
    for (int i = 1; i < n-1; i++) {
        if (arr[i-1] < arr[i] && arr[i] > arr[i+1]) {
            // Nếu phần tử hiện tại lớn hơn phần tử trước đó và lớn hơn phần tử sau đó
            // thì đó là đỉnh núi
            if (arr[i] > mtx) {  //nếu phần tử thỏa mãn tính chất đỉnh núi thì lưu lại
                mtx = arr[i];
                mti = i;
            }
        }
         else if(arr[0]>arr[1]){mtx=arr[0];mti=0;}  //tạm thời coi nó là đỉnh núi, tí check sau
        else if(arr[n-1]>arr[n-2]){mtx=arr[n-1];mti=n-1;}
    }
    // Kiểm tra tính chất tăng/giảm dần của dãy số
    if (mti == -3) {
        // Không tìm thấy đỉnh núi
        return false;
    }
    else if (mti == 0) {
        // Đỉnh núi ở phần tử đầu tiên
        for (int i = 1; i < n; i++) {
            if (arr[i] >= arr[i-1]) {  //nếu b>a thì đỉnh núi ko ở đầu tiên
                return false;
            }
        }
    }
    else if (mti == n-1) {
        // Đỉnh núi ở phần tử cuối cùng
        for (int i = n-2; i >= 0; i--) {
            if (arr[i] >= arr[i+1]) {  //nếu a>b thì không phải đỉnh núi ở cuối
                return false;
            }
        }
    }
    else {
        // Đỉnh núi ở giữa dãy số
        for (int i = 0; i < mti; i++) {
            if (arr[i] >= arr[i+1]) {
                return false;
            }
        }
        for (int i = mti; i < n-1; i++) {
            if (arr[i] <= arr[i+1]) {
                return false;
            }
        }
    }

    // Dãy số có hình dạng núi
    return true;
}

void findMaxiMini(vector <int >arr) {
    maxi = mini = 0; // Khởi tạo giá trị ban đầu cho maxi và mini

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > arr[maxi]) {
            maxi = i;
        }
        if (arr[i] < arr[mini]) {
            mini = i;
        }
    }
    cout<<" max min i la:"<<maxi<<" "<<mini<<endl;
}

int check_namma(int HP){
  for(int i=0;i<nammaMushGhost.size();i++){
     if(nammaMushGhost[i]==1){  
          findMaxiMini(chuoi_mush_ghost);
          HP-=(maxi+mini);
        cout<<" HP khi an nam 1:"<<HP<<endl;  
     }
     else if(nammaMushGhost[i]==2){
        if(check_nui(chuoi_mush_ghost)) cout<<"day nay la dinh nui\n";
        else cout<<"day nay ko phai dinh nui\n";
      HP-=(mtx + mti);
      cout<<" HP khi an nam 2:"<<HP<<endl;
     }
     else if(nammaMushGhost[i]==3){}
     else if(nammaMushGhost[i]==4){}
  }
  nammaMushGhost.clear();
 return HP;  
}

void set_sukien(char line[]) {  // hàm đọc sự kiện
    string str(line);
    int n = str.size();
    cout<<"str.size() ne:"<<str.size()<<endl;
    int num = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] != ' '&& str[i]!='\n') {
            num = num * 10 + (str[i] - '0');
        } 
        else if(str[i]!='\n'){
            sukien.push_back(num);
            num = 0;
        }
        else if(str[i]=='\n') break; 
    }
    if (num > 0) {  //nếu chuỗi line không kết thúc bằng khoảng trắng thì lưu giá trị vào sukien
        sukien.push_back(num);
    }
}

void set_file_dulieuthem(char line[]) {
    // Tach cac ten file trong chuoi line va luu vao mot mang tam thoi
    vector<string> file_names;   // tên các file
    char *token = strtok(line, ",");    //tách các kí tự trong chuỗi line ngăn cách nhau = ","
    while (token != NULL) {
        file_names.push_back(token);
        token = strtok(NULL, ",");
    }
    cout<<"hi:"<< file_names[0]<<endl<< file_names[1]<<endl<< file_names[2]<<endl;
    // Duyet qua tung file va doc du lieu tu cac file
    for (int i = 0; i < file_names.size(); i++) {
    ifstream file(file_names[i]);

    // Doc gia tri n va cac so nguyen tu file (neu file mo thanh cong)
    if (file) {
       if (file_names[i] == "tc1_mush_ghost"){
         int n;
         file>>n;
         string line;
         getline(file, line);
         getline(file, line);
   
       stringstream ss(line);
        for (int i = 0; i < n; i++) {
        string number;
        if (getline(ss, number, ',')) {
            chuoi_mush_ghost.push_back(stoi(number));
        }
    }
       }
       else if(file_names[i] == "tc1_merlin_pack"){}
       else if(file_names[i] == "tc1_aclepius_pack"){}
       

        file.close();
    }
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
    set_sukien(line);
    int MaxHP=HP;
    //lấy giá trị của hàng 3 trong file 
    fgets(line, N, fp);
    set_file_dulieuthem(line);


    for(int i=0;i<sukien.size();i++){  cout<<"dang chay qua ma su kien thu "<<i+1<<" sukien[i] la:"<<sukien[i]<<endl;   // nhớ xóa hàng này
         int j=i+1;  
         int b = j%10;
         int levelO = j > 6?(b > 5?b : 5) : b; 

         if(sukien[i]==0) {rescue=1;break;}   //nếu gặp sự kiện =0 thì thoát ra và hoàn thành chương trình

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
       
         else if(sukien[i]==11){  
           HP=set_HP(level,phoenixdown,HP);
           HP= HP>MaxHP?MaxHP:HP;
         }
         else if(sukien[i]==12){    //hiệp sĩ nhặt được nấm Fibonacci MushFibo
           if(HP>1) HP=setHP_fibonaci(HP);
         }
         else if(sukien[i]==13 ||sukien[i]>130){ 
             while(1){
                if(sukien[i]<100) break;
                nammaMushGhost.push_back(sukien[i]%10);
                sukien[i]/=10;
                
             }
             
             //đảo ngược giá trị của mảng nammaMushGost
             for (int j = 0; j < nammaMushGhost.size()/2; j++) {
                int temp = nammaMushGhost[j];
                nammaMushGhost[j] = nammaMushGhost[nammaMushGhost.size()-j-1];
                nammaMushGhost[i-j-1] = temp;
             }
             cout<<"nam ma mushghost tai i ne:";
             for(int m:nammaMushGhost) cout<<m<<endl;
              if(nammaMushGhost.size()>0) {HP=check_namma(HP);break;} 
             cout<<"mtx="<<mtx<<endl<<"mti="<<mti<<endl;
         }    
         else if(sukien[i]==15){   // nhặt được remedy
             remedy=remedy<99?(++remedy):remedy;
         }
         else if(sukien[i]==16){
            maidenkiss=maidenkiss<99?(++maidenkiss):maidenkiss;
         }
         else if(sukien[i]==17){
            phoenixdown=phoenixdown<99?(++phoenixdown):phoenixdown;
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