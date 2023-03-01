#include "knight.h"


//biến và mảng toàn cục:
vector< int > sukien;
vector< int > nammaMushGhost;    //số sự kiện nấm ma 
vector <int> chuoi_mush_ghost;   //lưu dữ liệu file mush ghost
int maxi,mini,max2_3x,max2_3i,maxi2,mini2,mtx=-2,mti=-3;  //dùng cho sự kiện ăn nấm
int** arr_aclepius;  //trỏ mảng 2 chiều lưu dữ liệu file aclepius sự kiện 19
string* chuoi_merlin;   //trỏ lưu các chuỗi quà trong file merlin sự kiện 18
int r1,c1; int solangapsukien19=0; int n9; int solangapsukien18=0;
bool checkHP_nammaMushGhost=0;

//khai báo hàm
float baseDamage(int);
int set_HP(int,int,int);
int setHP_fibonaci(int);
bool check_mountain(vector<int> );
void findMaxiMini(vector <int>,int);
void set_nammaloai3(vector<int>);
int check_namma(int,int,int &,bool &,bool &);
void set_sukien19( int &, int &, int &);
void set_sukien18(int &,int );
void set_sukien(string);
bool isInteger(string);
void set_file_line3(string);
bool check_Lancelot(int);


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

for(int i=99;i>10;i-=2){
    if(n1>0){
        s1+=i;
        n1--;
    }
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

int setHP_fibonaci(int HP){ // hàm nhập giá trị HP và trả về giá trị HP mới bằng số Fibonacci gần nhất
    int f1 = 0, f2 = 1, f3 = 1;
    while (f3 < HP)
    {
        f1 = f2;
        f2 = f3;
        f3 = f1 + f2;
    }
    return f2;
}

bool check_mountain(vector<int> arr) {   // dùng cho nấm ma loại 2
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
            // Nếu phần tử hiện tại lớn hơn phần tử trước đó và lớn hơn phần tử sau đó thì đó là đỉnh núi
            if (arr[i] > mtx) {  //nếu phần tử thỏa mãn tính chất đỉnh núi thì lưu lại
                mtx = arr[i];
                mti = i;
            }
        }
         else if(arr[0]>arr[1]){mtx=arr[0];mti=0;}  //tạm thời coi vị trí này là đỉnh núi
        else if(arr[n-1]>arr[n-2]){mtx=arr[n-1];mti=n-1;}
    }
    }
    // Kiểm tra tính chất tăng/giảm dần của dãy số
    if (mti == -3) {   mtx=-2;mti=-3;
        // Không tìm thấy đỉnh núi
        return false;
    }
    else if (mti == 0) {
        // Đỉnh núi ở phần tử đầu tiên
        for (int i = 1; i < n; i++) {
            if (arr[i] >= arr[i-1]) {  //nếu b>a thì đỉnh núi ko ở đầu tiên
                mtx=-2;mti=-3; return false;
            }
        }
    }
    else if (mti == n-1) {
        // Đỉnh núi ở phần tử cuối cùng
        for (int i = n-2; i >= 0; i--) {
            if (arr[i] >= arr[i+1]) {  //nếu a>b thì không phải đỉnh núi ở cuối
                mtx=-2;mti=-3; return false;
            }
        }
    }
    else {
        // Đỉnh núi ở giữa dãy số
        for (int i = 0; i < mti; i++) {
            if (arr[i] >= arr[i+1]) {
                mtx=-2;mti=-3; return false;
            }
        }
        for (int i = mti; i < n-1; i++) {
            if (arr[i] <= arr[i+1]) {
                mtx=-2;mti=-3; return false;
            }
        }
    }
    // Dãy số có hình dạng núi
    return true;
}

void findMaxiMini(vector <int >arr,int nammaMushGhost) {   //dùng cho nấm ma loại 1,3,4
    maxi = mini = maxi2 = mini2=0; // Khởi tạo giá trị ban đầu
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
    }

    else if(nammaMushGhost==4){
       //tìm số lớn thứ 2 và vị trí đầu tiên của số lớn thứ 2 đó trong 3 số arr[0] arr[1] arr[2]
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
    }   
}

void set_nammaloai3(vector<int> arr){
    for(int i=0;i<arr.size();i++){
        if(arr[i]<0) arr[i]=-arr[i];
        arr[i]= (17*arr[i] + 9)%257;
    }
}

int check_namma(int HP,int MaxHP,int &phoenixdown,bool &dangbienthanhtihon,bool &dangbienthanhech){ //dùng cho sự kiện 13
  for(int i=0;i<nammaMushGhost.size();i++){
     if(nammaMushGhost[i]==1){  
          findMaxiMini(chuoi_mush_ghost, nammaMushGhost[i]);
          HP=(HP-(maxi+mini))>MaxHP?MaxHP:(HP-(maxi+mini));
     }
     else if(nammaMushGhost[i]==2){
        check_mountain(chuoi_mush_ghost);
          HP=(HP-(mtx + mti))>MaxHP?MaxHP:(HP-(mtx + mti));
     }
     else if(nammaMushGhost[i]==3){
        vector<int> arr;
         for(int j=0;j<chuoi_mush_ghost.size();j++){
             arr.push_back(chuoi_mush_ghost[j]);
        }
        for(int i=0;i<arr.size();i++){
            if(arr[i]<0) {arr[i]=-arr[i];}           
        }
         for(int i=0;i<arr.size();i++){
            arr[i]= (17*arr[i]+9)%257 ;   //xi = (17 ∗ xi + 9)%257 
         }
        
        findMaxiMini(arr, nammaMushGhost[i]);  // tìm maxi2 và mini2
        HP=(HP-(maxi2 + mini2))>MaxHP?MaxHP:(HP-(maxi2 + mini2));

     }
     else if(nammaMushGhost[i]==4){
         vector<int> arr;
         for(int j=0;j<chuoi_mush_ghost.size();j++){
             arr.push_back(chuoi_mush_ghost[j]);
        }
        for(int i=0;i<arr.size();i++){
            if(arr[i]<0) {arr[i]=-arr[i];}           
        }
         for(int i=0;i<arr.size();i++){
            arr[i]= (17*arr[i]+9)%257 ;   //xi = (17 ∗ xi + 9)%257 
         }
        
         findMaxiMini(arr, nammaMushGhost[i]);    // tìm max2_3x và min2_3i
        HP=(HP-(max2_3x + max2_3i))>MaxHP?MaxHP:(HP-(max2_3x + max2_3i));
     }

  if(HP<=0) {           //check HP sau mỗi vòng
       if(phoenixdown>0){
        phoenixdown--;
        HP=MaxHP;
        if(dangbienthanhtihon==1) dangbienthanhtihon=0;
        if(dangbienthanhech==1) dangbienthanhech=0;
       }     
       else{ checkHP_nammaMushGhost=1; break;}
  }
 }
  nammaMushGhost.clear();
 return HP;  
}

void set_sukien19( int & remedy, int & maidenkiss, int & phoenixdown){
solangapsukien19++;
    for(int i=0;i<r1;i++){
        int thuocdalay=0; //số thuốc ăn được trên 1 hàng
        for(int j=0;j<c1;j++){
             if(arr_aclepius[i][j]==16 && thuocdalay<=2){   
                remedy=remedy<99?(++remedy):99;  thuocdalay++;
             }
             else if(arr_aclepius[i][j]==17 && thuocdalay<=2){
                maidenkiss=maidenkiss<99?(++maidenkiss):99;thuocdalay++;
             }
             else if(arr_aclepius[i][j]==18 && thuocdalay<=2){
                phoenixdown=phoenixdown<99?(++phoenixdown):99;thuocdalay++;
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
            HP += 3; HP=HP>MaxHP?MaxHP:HP; 
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
            if (!found) { HP+= 2; HP=HP>MaxHP?MaxHP:HP; /*nếu không rơi vào TH HP+3 thì chạy */ }
            check_m = false;
            check_e = false;
            check_r = false;
            check_l = false;
            check_i = false;
            check_n = false;
        }
    }
}

void set_sukien(string line) {
    stringstream ss(line);
    int num;
    while (ss >> num) {
        sukien.push_back(num);
    }
}

bool isInteger(string str) {  //dùng trong file mushghost, để check số nhập vào có phải số dương ko
    if (str.empty()) {  //check chuỗi rỗng
        return false;
    }
    // Kiểm tra dấu của số
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) {
            return false;
        }
        for (int i = 1; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
    }
    return true;
}

void set_file_line3(string line) {   //dùng cho hàng 3 của file tc1_input
     stringstream ss(line);
     string chuoi[3];
     for(int i=0;i<3;i++){
        getline(ss,chuoi[i],',');
     }

    for (int i = 0; i < 3; i++) {
     ifstream file(chuoi[i]); 
    // Doc gia tri n va cac so nguyen tu file (neu file mo thanh cong)
    if (file) {
        if (i==0 && chuoi[i]!=""){//tc1_mush_ghost   // file đọc sự kiện nấm sự kiện 13
         int n;
         file>>n;
         string line;
         getline(file, line);   //bỏ qua hàng đầu tiên đọc n
         getline(file, line);
   
        stringstream ss(line);
        for (int i = 0; i < n; i++) {
        string number;
          if(getline(ss, number, ',')) {
            if (isInteger(number)) { //nếu dữ liệu đọc vào là số nguyên
                 chuoi_mush_ghost.push_back(stoi(number));
            }
            //else "chuoi mush_ghost nhap vao khong hop le"
          }
        }
       }
       else if(i==1 && chuoi[i]!=""){//tc1_aclepius_pack  //file nhặt thuốc ở sự kiện 19
         string line; 
         file>>r1>>c1; 
         getline(file, line);
         int arr[r1][c1];  
         arr_aclepius = new int*[r1]; // Cấp phát mảng con trỏ cho các hàng
         for (int i = 0; i < r1; i++) {  
         arr_aclepius[i] = new int[c1]; // Cấp phát mảng con trỏ cho mỗi hàng
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
        
        // Gán giá trị cho mảng 2 chiều toàn cục
         for (int i = 0; i < r1; i++) {
             for (int j = 0; j < c1; j++) {
                 arr_aclepius[i][j] = arr[i][j];
             }
        }  
       }
       else if(i==2 && chuoi[i]!=""){//tc1_merlin_pack  // file chuỗi merlin ở sự kiện 18
       string line;
       file>>n9;
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
       }
    }
   file.close();
}
}

bool check_Lancelot(int HP){
    int souoc=0;
    for(int i=1;i<=HP;i++){
        if(HP%i==0) souoc++;
    }
    if(souoc==2) return 1;
    else return 0;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
  
    int trangthaitihon; //lưu giá trị i khi hiệp sĩ biến thành trangthaitihon
    rescue= -1;    int luu_level;int trangthaiech;  bool dangbienthanhtihon=0, dangbienthanhech=0; 
    // do trangthaitihon và trangthaiech chỉ nhận giá trị khi gặp sự kiện 6 và 7, nên để ktra điều kiện có dg bị trạng thái tí hon và trạng thái ếch hay không ta phải dùng 2 biến dangbienthanhtihon và dangbienthanhech, nếu nó =0 thì ko bị, =1 thì đang bị
    bool mode_Althur=0, mode_Lancelot=0;
     
    ifstream fp;
    string line;
    fp.open(file_input);
    getline(fp, line);       //lấy giá trị của hàng 1 trong file
    stringstream ss(line);   //dùng stringstream đọc tách các phần tử ra
    ss >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
    getline(fp, line);       //lấy giá trị của hàng 2 trong file
    set_sukien(line);
    getline(fp, line);       //lấy giá trị của hàng 3 trong file
    set_file_line3(line);
    fp.close();

     //check mode HP
     int MaxHP=HP; 
     if(MaxHP==999) mode_Althur=1; 
     mode_Lancelot=check_Lancelot(MaxHP);

    //thực hiện chạy sự kiện
    for(int i=0;i<sukien.size();i++){
         int j=i+1;  
         int b = j%10;
         int levelO = j > 6?(b > 5?b : 5) : b; 

         if(sukien[i]==0) {rescue=1;break;}   //nếu gặp sự kiện =0 thì thoát ra và hoàn thành chương trình

         else if(sukien[i]==6){     //gặp Shaman
            if(dangbienthanhech==1 || dangbienthanhtihon==1) goto label2;
             if(mode_Lancelot==1 || mode_Althur==1){
               if(level<=8)  level+=2;
               else if(level==9) level++;  
               goto label2;
             }
              if(level>levelO) {   
               if(level<=8)  level+=2;
               else if(level==9) level++;  
              }
              else if(level<levelO){
                if(remedy>0)
                {  
                  remedy--;  //nếu có thuốc remedy thì ko biến thành trạng thái tí hon
                }
                else 
                {
                  HP=HP<5?1:(HP/5) ; 
                  trangthaitihon=j; 
                  dangbienthanhtihon=1;
                }
              }

         label2:{}     
         }
         else if(sukien[i]==7){     //gặp Siren Vajsh
            if(dangbienthanhtihon==1 || dangbienthanhech==1) goto label1; 
            if(mode_Lancelot==1 || mode_Althur==1) {
                if(level<=8)  level+=2;
                else if(level==9) level++;  
                goto label1;
            }  
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
                level=1; 
                trangthaiech=j;
                dangbienthanhech=1;
              }
            }  
        label1:{}
         }
       
         else if(sukien[i]==11){    //nhặt được nấm tăng lực MushMario
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
                     if(i==0 && a/divisor!=1) break;  //nếu không phải mã sự kiện 13 thì bỏ qua sự kiện này và chạy sự kiện tiếp theo
                     if(i==1 && a/divisor!=3) break;
                     a %= divisor;
                     divisor /= 10;
                    
                 }
               }

              if(nammaMushGhost.size()>0) {HP=check_namma(HP,MaxHP,phoenixdown,dangbienthanhtihon,dangbienthanhech); HP>MaxHP?MaxHP:HP;}
              if(checkHP_nammaMushGhost==1) {rescue=0; break;}   // nếu đang ăn nấm ma mà HP<0 và ko có phoenixdown thì end game
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

                if(dangbienthanhtihon==1 && remedy>0){
                HP*=5;
                HP= HP>MaxHP?MaxHP:HP;   //nếu HP lớn hơn HP ban đầu thì giảm về HP ban đầu
                dangbienthanhtihon=0;
                remedy--; 
                }
                else if(dangbienthanhech==1 && maidenkiss>0){
                level=luu_level;
                dangbienthanhech=0;
                maidenkiss--; 
                } 
            }
            // else{ cout<<"do da gap su kien 19 roi nen khong chay nua"<<endl;}
         }
         else if(sukien[i]==99){   //gặp Bowser
            if((mode_Lancelot==1 && level>=8) || mode_Althur==1 || level>=10) {
                if(level<10) level=10;
            }
            else {rescue=0; break; }
         } 
         else if(sukien[i]==18){   //gặp phù thuỷ Merlin
             if(solangapsukien18<1){
                set_sukien18(HP,MaxHP);   
             }

         }

         else if(sukien[i]==1 || sukien[i]==2 || sukien[i]==3 || sukien[i]==4 || sukien[i]==5) {       //  các sự kiện còn lại
          if(mode_Lancelot==1 || mode_Althur==1) {
             if(level<10)  level++;
             goto label3;
          }
            if(level>levelO) {   //truyền sukien[i] vào biến loaidoithu
               if(level<10)  level++;  
            }
            else if(level<levelO) {
                int damage = baseDamage(sukien[i])*levelO*10;
                HP-=damage;
            }

          label3:{}
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


          //check HP sau mỗi vòng
          if(HP<=0) {           
            if(phoenixdown>0){
                phoenixdown--;
                HP=MaxHP;
                if(dangbienthanhtihon==1) dangbienthanhtihon=0;
                if(dangbienthanhech==1) dangbienthanhech=0;
            }
            else {rescue=0;break;}
          }
          
     if(HP>0 && i==sukien.size()-1) rescue=1;   //lưu lại giá trị rescue cho sự kiện cuối
     if(i<sukien.size()-1)  display(HP,level,remedy,maidenkiss,phoenixdown,rescue);
    }

  //in ra sự kiện kết thúc  
  display(HP,level,remedy,maidenkiss,phoenixdown,rescue);
  //giải phóng dữ liệu từ vector và con trỏ
  sukien.clear();
  chuoi_mush_ghost.clear();
  for (int i = 0; i < r1; i++) {  
                 delete[] arr_aclepius[i];
  }
  delete[] arr_aclepius; 
  delete[] chuoi_merlin;
}