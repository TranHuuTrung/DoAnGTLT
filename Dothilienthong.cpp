#include <iostream>
#include <fstream>
using namespace std;
#define MAX 100
char *DanhDau = new char [100];
char dinh[MAX];

//========== Input data from keyboard ==============
void inPutFromKeyBoard(int a[MAX][MAX], int &n)
{
	cout<<"Nhap so luong : ";
	cin>>n;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cin>>a[i][j];
		}
	}
}

//============ show data ============
void showData(int a[MAX][MAX], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		   {
				cout<<a[i][j]<<" ";
		   }
		cout<<"\n";
	}
}

//========== Input data form file =================
void inPutFromFile(int a[MAX][MAX], int &n)
{
	//doc du lieu tu file co san trong cung thu muc, chua cung voi file cpp
    ifstream DocFile("data.txt");
	//kiem tra xem co ton tai file ko
	if(!DocFile.is_open())
	{
		cout<<"Not open File :( "<<endl;
	}
	else
	{
		DocFile>>n;//nhap n tu file vao chuong trinh  
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				DocFile>>a[i][j];  //nhap cac gia tri cua file vao chuong trinh
			}
		}
	DocFile.close();
	//hienthi ra man hinh du lieu doc duoc tu file
    showData(a,n);
    }
}

//=============== check xem tat ca ca dinh co duong di giua chung ko ===============
int thamTatCaCacDinh(int a[][MAX], int n)
{
	//khoi tao 1 mang de chua cac dinh da duoc danh dau khi duyet qua do thi (chinh la mang DanhDau khai bao toan cuc)
	//ban dau khoi tao mang danh dau tat ca cac dinh deu la 0
	for(int i = 0; i < n; i++)
	{
		DanhDau[i] = 0;
	}
	//cho dinh bat dau danh dau la dinh dau thi danhdau = 1
	DanhDau[0] = 1;
    //khoi tao 1 biem de dem so dinh duoc tham
	int dem = 1; //khoi tao dem = 1 vi ta da gan tham dinh dau la 1
	for(int i = 0; i < n; i++)
	{
		if(DanhDau[i] == 1)  //neu dinh hien tai dang danh dau, kiem tra cac dinh ke no xem co duong di ko  
		{
			for(int j = 0; j < n; j++)
			{
				if(DanhDau[j] == 0 && a[i][j] == 1) //neu dinh do chua danh dau va co duong di giua chung thi danh dau diem do
				{
					DanhDau[j] = 1;
					dem++;        //tang so dinh duoc danh dau len
				}
			}
		}
	}
	if(dem == n) return 1; //neu giau tat ca cac dinh deu duoc ghe tham
	
	return 0;
}

//======================= check co huong hay khong ====================

int checkHuong(int a[][MAX], int n)
{
	//khai bao 1 mang 2 chieu chua gia tri la set chieu cho 2 dinh bat ki
	//neu co chieu tu dinh A->B thi gan la 1 else la 0
	//reset cho tat ca ban dau la 0
	//sau do duyet qua tat ca va set cho no 
	int coChieu[MAX][MAX];
	//khai bao 2 bien kieu int de dem chieu la motChieu, haiChieu;
	//neu chi co chieu tu A->B thi tang motChieu++
	//neu co ca A->B; B->A thi haiChieu++
	int motChieu = 0;
	int haiChieu = 0;
	//reset
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			coChieu[i][j] = 0;
		}
	}
	
	//duyet qua do thi va kiem tra xem chieu giua hai dinh la 1 chieu hay 2 chieu
	for(int i = 0; i < n; i++)
	{
		for(int j =0; j < n; j++)
		{
			//neu co chieu di tu A->B va chua danh dau co Chieu giua 2 canh thi se tang bien motChieu len
			if(a[i][j] == 1 && coChieu[i][j] == 0)
			{
				 motChieu++;
				//kiem tra tiep dieu kien B->A co chieu ko
			    //neu co chieu nua thi tro thanh 2 Chieu
			    if(a[j][i] == a[i][j])
			    {
			    	haiChieu++;
			    	//va cung danh dau lai cho coChieu[j][i] luon sau do ko xet nua
			    	coChieu[j][i] = 1;
		        }
			}
					
		}
	}
	
	//neu haiChieu = 0 thi tuc la khong co cac cap dinh nao trong do thi co chieu di qua lai voi nhau
	//se return ve 1
	if(haiChieu == 0)
	{
		return 1;  //so1 giong nhu no 1 chieu
	}
	else if(motChieu == haiChieu)  //neu hai gia tri nay bang nhau thi tuc la giua cac dinh nay co chieu qua lai voi nhau,
	{
		return 2; //so 2 giong nhu no 2 chieu
	}else
	{
		return 0;   //con lai cac truong hop khac
	}
	
}


//=============== Kiem tra lien thong ================
void checkLT(int a[][MAX], int n)
{
	int xoaChieu[MAX][MAX];
	//gan xoaChieu bang mang chua chieu a
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			xoaChieu[i][j] = 0;
		}
	}
	//th1: neu tham qua tat ca cac dinh thi chung ta se kiem tra tiep dieu kien la co huong hay khong
	//neu co huong thi do la lien thong manh
	//con nguoc lai la do thi vo huong lien thong
	
	if(thamTatCaCacDinh(a, n)  == 1)
	{
		if(checkHuong(a, n) == 1)//neu giua cac dinh co 1 chieu
		{
			cout<<"Do thi co huong Lien Thong Manh !"<<endl;
		}
		if(checkHuong(a, n) == 2) //neu giau hai dinh co 2 chieu
		{
			cout<<"Do thi vo huong Lien Thong !"<<endl;
		}
	}
	else
	{
		//th2: khong tham qua het tat ca cac dinh nhung chung ta se kiem tra no
	    //neu co huong nhung khi bo huong di thi no tro thanh lien thong thi chung ta ket luan do la lien thong yeu
	    //nguoc lai thi do thi khong lien thong
	    if(checkHuong(a, n) == 0)  //co huong
	    {
	    	//minh se tao ra 1 mang 2 chieu de xet xem cai do thi khi minh bo chieu di co lien thong khong
	    	for(int i = 0; i < n; i++)
	    	{
	    		for(int j = 0; j < n; j++)
	    		{
	    			if(a[i][j] == 1)  // cai nay la 1 chieu tu A->B cua 2 dinh bat ki trong do thi co huong
	    			{
	    				//gan lai cho no tro thanh vo huong xoaChieu[i][j] = xoaChieu[j][i]
	    				xoaChieu[i][j] = a[i][j]; 
	    				xoaChieu[j][i] = a[i][j];
	    			}
	    		}
	    	}
	    //sau khi da chuyen do thi co huong thanh vo huong chung ta bat dau check do co lien thong khong
	    //tuc la chung ta goi ham tham tat ca cac dinh
            if(thamTatCaCacDinh(xoaChieu,n) == 1)
	        {
			     cout<<"Do thi co huong Lien thong Yeu !"<<endl;
		    }  
            else
	        {
	    	     cout<<"Khong Lien Thong !"<<endl;
	        }
	    	
	    }
	    else
	    {
	    	cout<<"Khong Lien Thong !"<<endl;
	    }
		
		
	}
}

//================= Chuong trinh chinh =================
int main()
{
 int a[MAX][MAX];
	int n,s;
	int in;
	cout<<endl<<"\n======= KIEM TRA TINH LIEN THONG CUA DO THI =======\n";
    cout<<"\t1. Nhap tu ban phim"<<endl;
    cout<<"\t2. Doc tu file "<<endl;
    cout<<"\t3. Kiem tra lien thong"<<endl;
    cout<<"\t4. Thoat"<<endl;
    cout<<"==================================================="<<endl;
   	cout<<endl;
    do{
    	cout<<"Moi ban chon thao tac:  ";
    	cin>>in;
   
		switch(in){
		case 1:
			inPutFromKeyBoard(a,n);
			break;
		case 2:
			inPutFromFile(a,n);
			break;
		case 3:
			checkLT(a,n);
			break;
		case 4:
			exit(0);
		default:
			cout<<"Moi ban chon lai!!!"<<endl;
			break;
	     } 	
      }while(in);
	return 0;
}
