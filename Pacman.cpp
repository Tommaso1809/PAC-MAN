/*Author:Tommaso Polvere 3CI
 *Name:Pacman
 *Description:Implementazione del Pacman Naive in C++,muoviti con i tasti WASD
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
using namespace std;

void stampa_mappa(char[][32]);
void genera_posizione(char[][32]);
void controllo(char[][32]);
char pacman={'@'};

char enemy={'x'};
int a,b,i=1,j=1;
char tasto;

int main(){
    
    srand(time(NULL));
	
	
	cout<<"BENVENUTO IN PACMAN !! "<<endl;
	cout<<"TU = @ \n";
	cout<<"NEMICO = x \n";
	cout<<"\n";
	sleep(2);
	    
   char mappa[32][32] = {
	"###############################",
	"#                             #",
	"#                             #",
	"### ########### ##   ##########",
	"#                             #",
	"#  ###        #####           #",
	"#          ###    #####       #",
	"########         ##           #",
	"#           ###               #",
	"# ##### ###         ##        #",
	"#          ######  ####### ####",
	"#                             #",
	"## ### ####      ###   ########",
	"#           ####     #        #",
	"#                             #",
	"#   ##########   ##########   #",
	"#                             #",
	"###############################"
	};
	
	

    mappa[i][j]=pacman;

    genera_posizione(mappa);


   return 0; 
}

void stampa_mappa(char mappa[][32]){

	
    for(int i=0;i<18;i++){

        for(int j=0;j<32;j++){

            cout<<mappa[i][j];
            
        }
        cout<<endl;
    }
        
}

void genera_posizione(char mappa[][32]){

    char scelta;
    
    do{
        i=1,j=1;
        mappa[i][j]=pacman;
        a=rand()%16+1;
        b=rand()%30+1;
        mappa[a][b]=enemy;

        stampa_mappa(mappa);
    
        controllo(mappa);
        
        
            
        cout<<endl;
        cout<<"HAI VINTO BRAVO/A !!!!"<<endl;
        cout<<endl;
        mappa[i][j]=' ';
        cout<<"Vuoi Giocare ancora s|n "<<endl;
        cin>>scelta;
        system("CLS");
    }while(scelta!='n');

    cout<<"GAME FINISH"<<endl;
  
}

void controllo(char mappa[][32] ){
    
    cout<<"Muoviti con i tasti WASD"<<endl;

    do{
    
         tasto=getch();
        
         switch(tasto){
        
        case 'w':
           
            if(mappa[i-1][j]!='#'){

                i--;
                mappa[i+1][j]=' ';
                mappa[i][j]=pacman;
            	system("CLS");
            }
            
             stampa_mappa(mappa);
             
        	
        break;
        
        case 'a':

            if(mappa[i][j-1]!='#'){
                
                  j--;
                mappa[i][j+1]=' ';
                mappa[i][j]=pacman;
                
                system("CLS");
            }

             stampa_mappa(mappa);
            
        
        break;
        
        case 's':
            
            if(mappa[i+1][j]!='#'){
                
                 i++;
                mappa[i-1][j]=' ';
                mappa[i][j]=pacman;
                
                system("CLS");
            }

            stampa_mappa(mappa);

            
        break;
        
        case 'd':
        
            if(mappa[i][j+1]!='#'){
                
                j++;
                mappa[i][j-1]=' ';
                mappa[i][j]=pacman;

				system("CLS");	
            }
            
            stampa_mappa(mappa);
        break;    
            
        }
     
        
    
    }while(mappa[i][j]!=mappa[a][b]);

}    
