#include "knight.h"
#include <vector>
using namespace std;

// bug dãy núi có 2 hoặc 2 phần tử


//khai báo hàm
void display(int,int,int,int,int,int);
void adventureToKoopa(string,int &,int &,int &,int &,int &,int &);
float baseDamage(int);
void set_sukien(char);
void set_file_dulieuthem(char);
int set_HP(int,int,int);
int setHP_fibonaci(int);
int check_namma(int,int,int &,bool &,bool &);
bool check_nui(vector<int> );
void findMaxiMini(vector <int>);
void set_nammaloai3(vector<int>);
void set_sukien19( int & remedy, int & maidenkiss, int & phoenixdown);
void set_sukien18(int &HP,int MaxHP);
bool check_Lancelot(int);
bool checkHP_nammaMushGhost=0;

//biến và mảng toàn cục:
 vector< int > sukien;
vector< int > nammaMushGhost;
vector <int> chuoi_mush_ghost;
int maxi,mini,max2_3x,max2_3i,maxi2,mini2,mtx=-2,mti=-3;
int** arr_aclepius;
int r1,c1; int solangapsukien19=0; int n9; int solangapsukien18=0;
string* chuoi_merlin;



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

bool check_nui(vector<int> arr) {   // dùng cho nấm ma loại 2
    int n = arr.size();
    // Tìm đỉnh núi
    if(n==1) {mtx=arr[0];mti=0;}
    else if(n==2) {
        if(arr[0]>arr[1]){
            mtx=arr[0];mti=0;
        }
        else if(arr[0]<arr[1]){
            mtx=arr[1];mti=1;
        }
    }
    else {
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

void findMaxiMini(vector <int >arr,int nammaMushGhost) {   //dùng cho nấm ma loại 1 và loại 3
    maxi = mini = maxi2 = mini2=0; // Khởi tạo giá trị ban đầu cho maxi và mini
    max2_3x=-5; max2_3i=-7;
    if(nammaMushGhost==1){
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] >= arr[maxi]) {
            maxi = i;
        }
        if (arr[i] <= arr[mini]) {
            mini = i;
        }
    }  
    cout<<" max min i la:"<<maxi<<" "<<mini<<endl;
    }
    
    else if(nammaMushGhost==3){
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > arr[maxi2]) {
            maxi2 = i;
        }
        if (arr[i] <arr[mini2]) {
            mini2 = i;
        }
    }
    cout<<" max min i2 la:"<<maxi2<<" "<<mini2<<endl;        
    }

    else if(nammaMushGhost==4){
       //tìm số lớn thứ 2 và vị trí đầu tiên của số lớn thứ 2 đó trong 3 số này arr[0] arr[1] arr[2]
       if(arr.size()==1){   /*không biến đổi max2_3x,min2_3i  */  }
       else if(arr.size()==2){
         if(arr[0]>arr[1]){
            max2_3x=arr[1]; max2_3i=1;
         }
         else if(arr[0]<arr[1]){
            max2_3x=arr[0]; max2_3i=0;
         }
         else { /* không biến đổi max2_3x,min2_3i với TH 2 số bằng nhau */} 

       }
       else if(arr.size()>=3){
           if(arr[0]==arr[1]==arr[2]){/* không biến đổi max2_3x,min2_3i với TH 3 số bằng nhau*/ }
           else{  // chỉ còn 2 TH là 2 số bằng nhau và không có số nào bằng nhau
               int max=arr[0];
               for(int i=1;i<3;i++){      //tìm số lớn nhất trong 3 số
                   if(arr[i]>max) max=arr[i];
               }
               
               for(int j=0;j<2;j++){      //tìm số lớn thứ 2 và vị trí đầu tiên
                   if((arr[j]<max)) {
                       max2_3x=arr[j]; max2_3i=j; break; 
                   }
               }
           }          
       } 
       cout<<"max2_3x,min2 la:"<<max2_3x<<" "<<max2_3i<<endl; 
    }   
}

void set_nammaloai3(vector<int> arr){
    for(int i=0;i<arr.size();i++){
        if(arr[i]<0) arr[i]=-arr[i];
        arr[i]= (17*arr[i] + 9)%257;
    }
}

int check_namma(int HP,int MaxHP,int &phoenixdown,bool &dangbienthanhtihon,bool &dangbienthanhech){        //dùng cho sự kiện 13
  for(int i=0;i<nammaMushGhost.size();i++){
     if(nammaMushGhost[i]==1){  
          findMaxiMini(chuoi_mush_ghost, nammaMushGhost[i]);
          HP-=(maxi+mini);
        cout<<" HP khi an nam 1:"<<HP<<endl;  
     }
     else if(nammaMushGhost[i]==2){
        if(check_nui(chuoi_mush_ghost)) cout<<"day nay la dinh nui\n";
        else cout<<"day nay ko phai dinh nui\n";
      HP-=(mtx + mti);
      cout<<" HP khi an nam 2:"<<HP<<endl;
     }
     else if(nammaMushGhost[i]==3){
        vector<int> arr;
        for(int i=0;i<chuoi_mush_ghost.size();i++){
            if(chuoi_mush_ghost[i]<0) {chuoi_mush_ghost[i]=-chuoi_mush_ghost[i];}           
        }
         cout<<"chuoi sau khi check am duong:";
         for(int i:chuoi_mush_ghost) cout<<i<<" ";cout<<endl;

        for(int j=0;j<chuoi_mush_ghost.size();j++){
            arr.push_back(  (17*chuoi_mush_ghost[j]+9)%257  );  //xi = (17 ∗ xi + 9)%257   
        }
        cout<<"chuoi sau khi bien doi:";
         for(int i:arr) cout<<i<<" ";
         cout<<endl;
        findMaxiMini(arr, nammaMushGhost[i]);  // tìm maxi2 và mini2
        HP -=(maxi2 + mini2);

     }
     else if(nammaMushGhost[i]==4){
         vector<int> arr;
        for(int i=0;i<chuoi_mush_ghost.size();i++){
            if(chuoi_mush_ghost[i]<0) {chuoi_mush_ghost[i]=-chuoi_mush_ghost[i];}           
        }
         cout<<"chuoi sau khi check am duong:";
         for(int i:chuoi_mush_ghost) cout<<i<<" ";cout<<endl;

        for(int j=0;j<chuoi_mush_ghost.size();j++){
            arr.push_back(  (17*chuoi_mush_ghost[j]+9)%257  );  //xi = (17 ∗ xi + 9)%257   
        }
        cout<<"chuoi sau khi bien doi:";
         for(int i:arr) cout<<i<<" ";
         cout<<endl;
         findMaxiMini(arr, nammaMushGhost[i]);    // tìm max2_3x và min2_3i
        HP -=(max2_3x + max2_3i);
         cout<<" HP khi an nam 4:"<<HP<<endl;
     }

  if(HP<=0) {           //check HP sau mỗi vòng
       if(phoenixdown>0){ cout<<"do bi chet nen phai dung phoemixdown\n"; 
        phoenixdown--;
        HP=MaxHP;
        if(dangbienthanhtihon==1) dangbienthanhtihon=0;
        if(dangbienthanhech==1) dangbienthanhech=0;
       }     
       else{ cout<<"HP="<<HP; cout<<" khi an nam thu "<<i+1<<" nen ket thuc CT\n";   checkHP_nammaMushGhost=1; break;}
  }
 }
  nammaMushGhost.clear();
 return HP;  
}

void set_sukien19( int & remedy, int & maidenkiss, int & phoenixdown){
solangapsukien19++;
    for(int i=0;i<r1;i++){
        int remedy1=0,maidenkiss1=0,phoenixdown1=0;
        for(int j=0;j<c1;j++){
             if(arr_aclepius[i][j]==16 && remedy1<=2){   
                remedy++;remedy1++;
             }
             else if(arr_aclepius[i][j]==17 && maidenkiss1<=2){
                maidenkiss++;maidenkiss1++;
             }
             else if(arr_aclepius[i][j]==18 && phoenixdown1<=2){
                phoenixdown++;phoenixdown1++;
             }
        }
    }
}

void set_sukien18(int &HP,int MaxHP){
solangapsukien18++;
bool check_m = false, check_e = false, check_r = false, check_l = false, check_i = false, check_n = false;

for (int i = 0; i < n9; i++) {
        string chuoi = chuoi_merlin[i];
        bool found = false;
        // Kiểm tra chuỗi "merlin" hoặc "Merlin"
        if (chuoi.find("merlin") != string::npos || chuoi.find("Merlin") != string::npos) {
            HP += 3; HP=HP>MaxHP?MaxHP:HP; cout<<"da gap chuoi merlin va tang HP+3 len maxHP\n";
            found = true;
        }

        // Kiểm tra các chữ cái "m", "e", "r", "l", "i", "n"
        for (char& c : chuoi) {
            if (tolower(c) == 'm') {
                check_m = true;
            } else if (tolower(c) == 'e') {
                check_e = true;
            } else if (tolower(c) == 'r') {
                check_r = true;
            } else if (tolower(c) == 'l') {
                check_l = true;
            } else if (tolower(c) == 'i') {
                check_i = true;
            } else if (tolower(c) == 'n') {
                check_n = true;
            }
        }
        // Nếu đủ 6 chữ cái "m", "e", "r", "l", "i", "n"
        if (check_m && check_e && check_r && check_l && check_i && check_n) {
            if (!found) { HP+= 2; HP=HP>MaxHP?MaxHP:HP; /*nếu không rơi vào TH HP+3 thì chạy */ cout<<"da gap chuoi merlin va tang HP+2 len maxHP\n"; }
            check_m = false;
            check_e = false;
            check_r = false;
            check_l = false;
            check_i = false;
            check_n = false;
        }
    }
}

void set_sukien(char line[]) {  // hàm đọc sự kiện của dòng 2 file tc1_input
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
        else if(str[i]=='\n') { sukien.push_back(num);  break; }
    }
    // if (num > 0) {  //nếu chuỗi line không kết thúc bằng khoảng trắng thì lưu giá trị vào sukien
    //     sukien.push_back(num);
    // }
}

void set_file_dulieuthem(char line[]) {   //dùng cho hàng 3 của file tc1_input
    // Tach cac ten file trong chuoi line va luu vao mot mang tam thoi
    vector<string> file_names;   // tên các file
    char *token = strtok(line, ",");    //tách các kí tự trong chuỗi line ngăn cách nhau = ","
    while (token != NULL) {
        file_names.push_back(token);
        token = strtok(NULL, ",");
    }
    cout<<"day la ten 3 file da doc:"<< file_names[0]<<endl<< file_names[1]<<endl<< file_names[2]<<endl;
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
       else if(file_names[i] == "tc1_aclepius_pack"){
         string line;
         file>>r1>>c1;   cout<<" r1 va c1 la:"<<r1<<" "<<c1<<endl;
         getline(file, line);
         int arr[r1][c1];
         arr_aclepius = new int*[r1]; // Cấp phát mảng con trỏ cho các hàng
         for (int i = 0; i < r1; i++) {
         arr_aclepius[i] = new int[c1]; // Cấp phát mảng cho mỗi hàng
         }       
         for(int i=0;i<r1;i++){
            getline(file, line);
            stringstream ss(line);
             for(int j=0;j<c1;j++){
                 string number;
                 if (getline(ss, number, ' ')){
                   arr[i][j]=stoi(number);
                 }
             }
         }
        
        // Gán giá trị cho mảng 2 chiều
         for (int i = 0; i < r1; i++) {
             for (int j = 0; j < c1; j++) {
                 arr_aclepius[i][j] = arr[i][j];
             }
        }

         for(int i=0;i<r1;i++){    // vòng for này chỉ để in gtri để check, về sau nhớ bỏ
            cout<<"day la gia tri cua hang "<<i+1<<":";
            for(int j=0;j<c1;j++){
                cout<< arr_aclepius[i][j]<<" ";
            }
            cout<<endl;
         }  
       }
       else if(file_names[i] == "tc1_merlin_pack"){
       string line;
       file>>n9; cout<<"n9 la:"<<n9<<endl;
       getline(file, line);
       chuoi_merlin= new string[n9];
       for(int i=0;i<n9;i++){
            getline(file, line);
            stringstream ss(line);
            string chuoi;
            if (getline(ss, chuoi)){
                   chuoi_merlin[i]=chuoi;
            }
       }
       cout<<"chuoi_merlin da doc la:\n";
       for(int i=0;i<n9;i++) cout<<chuoi_merlin[i]<<endl;
       }
       
       

        file.close();
    }
}
}

bool check_Lancelot(int HP){
    int soUC=0;
    for(int i=1;i<=HP;i++){
        if(HP%i==0) soUC++;
    }
    if(soUC==2) return 1;
    else return 0;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    #define N 256 
    FILE * fp=NULL;
    char line[N];  int trangthaitihon; //lưu giá trị i khi hiệp sĩ biến thành trangthaitihon
    rescue= -1;        int luu_level;int trangthaiech;  bool dangbienthanhtihon=0, dangbienthanhech=0; 
    // do trangthaitihon và trangthaiech chỉ nhận giá trị khi gặp sự kiện 6 và 7, nên để ktra điều kiện có dg bị trạng thái tí hon và trạng thái ếch hay không ta phải dùng 2 biến dangbienthanhtihon và dangbienthanhech, nếu nó =0 thì ko bị, =1 thì đang bị
    bool mode_Althur=0, mode_Lancelot=0;

    fp=fopen("tc1_input","r"); 
    //lấy giá trị của hàng 1 trong file
    fgets(line, N, fp);
    sscanf(line,"%d %d %d %d %d", &HP, &level, &remedy, &maidenkiss, &phoenixdown);
    //lấy giá trị của hàng 2 trong file  
    fgets(line, N, fp);
    set_sukien(line);
    //lấy giá trị của hàng 3 trong file 
    fgets(line, N, fp);
    set_file_dulieuthem(line);
     
     int MaxHP=HP; 
     if(MaxHP==999) mode_Althur=1; 
     mode_Lancelot=check_Lancelot(MaxHP);

cout<<"so su kien da duoc luu:"<<sukien.size()<<endl;

    for(int i=0;i<sukien.size();i++){  cout<<"dang chay qua ma su kien thu "<<i+1<<" sukien[i] la:"<<sukien[i]<<endl;   // nhớ xóa hàng này
         int j=i+1;  
         int b = j%10;
         int levelO = j > 6?(b > 5?b : 5) : b; 

         if(sukien[i]==0) {rescue=1;break;}   //nếu gặp sự kiện =0 thì thoát ra và hoàn thành chương trình

         else if(sukien[i]==6){     //gặp Shaman
         if(dangbienthanhech==1 || dangbienthanhtihon==1 || mode_Lancelot==1 || mode_Althur==1){cout<<"do dang bi buff or Lancelot nen khong danh voi shaman"<<endl; goto label2;}
              if(level>levelO) {   
               if(level<=8)  level+=2;
               else if(level==9) level++;  
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
                  dangbienthanhtihon=1;
                }
              }

         label2:{}     
         }
         else if(sukien[i]==7){
            if(dangbienthanhtihon==1 || dangbienthanhech==1 || mode_Lancelot==1 || mode_Althur==1) {cout<<"do dang bi buff or Lancelot nen khong danh voi Siren Vajsh "<<endl; goto label; }  //nếu đang ở trạng thái tí hon thì không thực hiện hàm
            if(level>levelO) {   
               if(level<=8)  level+=2;
               else if(level==9) level++;  
            }
            else if(level<levelO){
              if(maidenkiss>=1){
                maidenkiss--;
              }            
              else {
                luu_level=level;  //lưu lại level khi bị thua để sau khi hồi phục trở lại level trước khi biến thành ếch
                level=1;   cout<<"do thua Vajsh nen level tro ve 1\n";
                trangthaiech=j;
                dangbienthanhech=1;
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
              int a=sukien[i];
              int divisor = 1;
              int numDigits = 0;

            // Xác định số chữ số và divisor cho 2 chữ số đầu tiên
              while (a / divisor >= 10) {
                divisor *= 10;
                numDigits++;
              }
               // Tách các chữ số còn lại và thêm chúng vào vector kết quả
              for (int i = 0; i <= numDigits; i++) {
                if(i>=2){
                     nammaMushGhost.push_back(a / divisor);
                     a %= divisor;
                     divisor /= 10;
                }
                 else{
                     a %= divisor;
                     divisor /= 10;
                 }
               }

             cout<<"nam ma mushghost tai i ne:";
             for(int m:nammaMushGhost) cout<<m<<endl;
              if(nammaMushGhost.size()>0) {HP=check_namma(HP,MaxHP,phoenixdown,dangbienthanhtihon,dangbienthanhech);}
              if(checkHP_nammaMushGhost==1) break; 
         }    
         else if(sukien[i]==15){   // nhặt được remedy
             remedy=remedy<99?(++remedy):remedy;
             if(dangbienthanhtihon==1){
                HP*=5;
                HP= HP>MaxHP?MaxHP:HP;   //nếu HP lớn hơn HP ban đầu thì giảm về HP ban đầu
                dangbienthanhtihon=0;
                remedy--;
            }
         }
         else if(sukien[i]==16){
            maidenkiss=maidenkiss<99?(++maidenkiss):maidenkiss;
            if(dangbienthanhech==1){
              level=luu_level;
              dangbienthanhech=0;
              maidenkiss--;
            }
         }
         else if(sukien[i]==17){
            phoenixdown=phoenixdown<99?(++phoenixdown):phoenixdown;
         }
         else if(sukien[i]==19){
            if(solangapsukien19<1) {
                set_sukien19(remedy,maidenkiss,phoenixdown);

                if(dangbienthanhtihon==1){
                HP*=5;
                HP= HP>MaxHP?MaxHP:HP;   //nếu HP lớn hơn HP ban đầu thì giảm về HP ban đầu
                dangbienthanhtihon=0;
                remedy--;   cout<<"remedy -1 de giaitrutrangthai tihon"<<endl;
                }
                else if(dangbienthanhech==1){
                level=luu_level;
                dangbienthanhech=0;
                maidenkiss--; cout<<"maidenkiss -1 đe giaitrutrangthai ech"<<endl;
                } 
            }
            else{ cout<<"do da gap su kien 19 roi nen khong chay nua"<<endl;}
            cout<<"thuoc sau khi gap su kien 19 va giaitrutrangthai la:"<<remedy<<" "<<maidenkiss<<" "<<phoenixdown<<endl;
         }
         else if(sukien[i]==99){   //gặp Bowser
            if((mode_Lancelot==1 && level>=8) || mode_Althur==1 || level>=10) {
                if(level<10) level=10;
                cout<<"gap phai trum roi nen Bowser nay xin thua\n";
                }
            else {cout<<"thua Bower nen end game\n";rescue==0; break; }
         }
         else if(sukien[i]==18){   //gặp phù thuỷ Merlin
             if(solangapsukien18<1){
                set_sukien18(HP,MaxHP);   
             }
             else cout<<"do da gap sukien 18 roi nen se khong chay nua\n";
         }

         else {       //  các sự kiện còn lại
          if(mode_Lancelot==1 || mode_Althur==1) {cout<<"gap thang choa Lancelot or thang BOSS Althur roi nen tao xin thua\n"; goto label3;}
            if(level>levelO) {   //truyền sukien[i] vào biến loaidoithu
               if(level<10)  level++;  
            }
            else if(level<levelO) {
                int damage = baseDamage(sukien[i])*levelO*10;
                HP-=damage;
            }


            //check nếu đã qua ba màn thì hiệp sĩ trở về bình thường
            if(j>=trangthaitihon+3 && dangbienthanhtihon==1){
                HP*=5;
                HP= HP>MaxHP?MaxHP:HP;   //nếu HP lớn hơn HP ban đầu thì giảm về HP ban đầu
                dangbienthanhtihon=0;
            }
            if(j>=trangthaiech+3 && dangbienthanhech==1){
              level=luu_level;
              dangbienthanhech=0;
            }
          label3:{}
         }
         


          if(HP<=0) {           //check HP sau mỗi vòng
            if(phoenixdown>0){ cout<<"do bi chet nen phai dung phoemixdown\n"; 
                phoenixdown--;
                HP=MaxHP;
                if(dangbienthanhtihon==1) dangbienthanhtihon=0;
                if(dangbienthanhech==1) dangbienthanhech=0;
            }
            
            else {rescue=0;break;}
          }
          
          if(HP>0 && i==sukien.size()-1) rescue=1;   //lưu lại giá trị rescue cho sự kiện cuối
      display(HP,level,remedy,maidenkiss,phoenixdown,rescue); // nhớ xóa hàng này
    }
   display(HP,level,remedy,maidenkiss,phoenixdown,rescue);

}

