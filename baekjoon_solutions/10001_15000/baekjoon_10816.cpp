#include <iostream>
#include <map>

using namespace std;

int main(){
    ios::sync_with_stdio(false);

    cin.tie(nullptr);
	cout.tie(nullptr);
    
    int N, M;
    map<int, int> get_card;
    cin >> N;
    for(int i=0;i<N;i++){
        int tmp = 0;
        cin >> tmp;
        if (get_card.find(tmp) != get_card.end()){
            get_card[tmp] += 1;
        }
        else{
            get_card.insert({tmp, 1});
        }
    }
    cin >> M;
    for(int i=0;i<M;i++){
        int tmp2 = 0;
        cin >> tmp2;
        if (get_card.find(tmp2) != get_card.end()){
            cout << get_card[tmp2] << " ";
        }
        else{
            cout << "0 ";
        }
    }
}