#include<bits/stdc++.h>
using namespace std;
#define ll long
#define br cout<<"\n";
const long n=10;


// ok=0 means first player (X)
// ok=1 means second player (O)
ll ok=0;
vector<char>board(n);
char Human,Bot;

void initilize_board(){
    for(ll i=1;i<n;i++){
        board[i]='0'+i;
    }
}

bool is_continue(){
    // check baoard is full or not
    for(ll i=1;i<n;i++){
        if(board[i]!='X' and board[i]!='O')return true;
    }
    return false;
}

void print_board(){
    // printing board exactly like a tic tac toe
    br;
    for(ll i=1;i<n;i++){
        if( i!=1 and (i-1)%3==0){
            br; cout<<"---------";br;
        }
        cout<<board[i];
        if(i%3!=0)cout<<" | ";
    }br;
}

bool is_valid_move(ll response){
    // is valid move ?
    if(response<n and response>0 and (board[response]!='X' or board[response]!='O'))return true;
    return false;
}

ll is_win(){

    // -10 if You win, 10 if computer win and 0 if tie

    for(ll i=1;i<n;i+=3){
        if(board[i]==Human and board[i+1]==Human and board[i+2]==Human)return -10;
        if(board[i]==Bot and board[i+1]==Bot and board[i+2]==Bot)return 10;
    }

    for(ll i=1;i<=3;i++){
        if(board[i]==Human and board[i+3]==Human and board[i+6]==Human)return -10;
        if(board[i]==Bot and board[i+3]==Bot and board[i+6]==Bot)return 10;
    }

    if(board[1]==Human and board[5]==Human and board[9]==Human)return -10;
    if(board[1]==Bot and board[5]==Bot and board[9]==Bot)return 10;

    if(board[3]==Human and board[5]==Human and board[7]==Human)return -10;
    if(board[3]==Bot and board[5]==Bot and board[7]==Bot)return 10;
    
    return 0;
}

ll minimax(bool ismax){

    ll score=is_win();
    if(score==10 or score==-10)return score;
    if(!is_continue())return 0;

    if(ismax){
        // computer
        ll best=-1e5;

        for(ll i=1;i<n;i++){
            if(board[i]!='X' and board[i]!='O'){
                char initially=board[i];

                board[i]=Bot;
                best=max(best,minimax(!ismax));

                board[i]=initially;

            }
        }
        return best;
    }
    else{
        // player
        ll best=1e5;

        for(ll i=1;i<n;i++){
            if(board[i]!='X' and board[i]!='O'){
                char initially=board[i];

                board[i]=Human;
                best=min(best,minimax(!ismax));

                board[i]=initially;

            }
        }
        return best;
    }
}

ll computer(){

    ll best=-1e6;
    ll index=-1;

    for(ll i=1;i<n;i++){
        if(board[i]!='X' and board[i]!='O'){
            char initially=board[i];

            board[i]=Bot;
            ll curr_move_score=minimax(false);

            // undo step
            board[i]=initially;

            if(curr_move_score>best){
                best=curr_move_score;
                index=i;
            }
        }
    }

    return index;
}

void perform_move(){

    while(true){

        ll take_response;

        if(!ok){
            cout<<"Your Turn: ";
            cin>>take_response;
        }
        else{
            cout<<"Computer Turn: ";
            take_response=computer();
            cout<<take_response;
        }

        if(!is_valid_move(take_response)){
            cout<<"Invalid Move, Enter again!!";br;
        }
        else{
            board[take_response]=(ok==0?Human:Bot);
            break;
        }
    }

    ok=1-ok;
}


void solve(){


    initilize_board();
    print_board();
    
    while(is_continue()){

        perform_move();
        print_board();

        if(is_win()==10){
            cout<<"COMPUTER WIN!!";br; 
            print_board();return;
        }
        else if(is_win()==-10){
            cout<<"YOU WIN!!";br;
            print_board(); return;
        }
        
    }

    cout<<"GAME DRAW!!";br;
    print_board();

}

int main(){

    cout<<"Which symbol (X or O, X goes first)? ";
    cin>>Human;

    ok=(Human=='X'?0:1);

    Bot=(Human=='X'?'O':'X');
    
    solve();
}
