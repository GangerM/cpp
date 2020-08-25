#include "priorityqueue.cpp"
#include "teamdata.cpp"
#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
    char* fileName = argv[1];
    std::ifstream file;
    file.open(fileName);

    nlohmann::json jsonObject, jsonPrint;

    if (file.is_open()) file >> jsonObject;

    size_t numPlayers = jsonObject["metadata"]["numPlayers"];

    TeamData data;
    PriorityQueue tree(numPlayers);

    for (auto& x: jsonObject["teamStats"]){
        int y = x["playerOne"];
        int z = x["playerTwo"];
        double winp = x["winPercentage"];

        double bal = 50 - winp;
        if (bal < 0) bal *= -1;

        tree.insert(std::make_pair(bal, std::make_pair(y , z)));

       // tree.insert(std::make_pair( , );
    }

    /*
    std::vector<std::pair<int,int>> teams;
    for (int i = 0; i < numPlayers/2; i++){
        std::pair<int,int> players = tree.removeMin().second;
        teams.push_back(players);
        int playerOne = players.first;
        int playerTwo = players.second;

        for(int i = 1; i < tree.returnSize()+1; i+=0) {
            if (tree.returnKvp(i).second.first == playerOne || tree.returnKvp(i).second.second == playerOne ||
                tree.returnKvp(i).second.first == playerTwo || tree.returnKvp(i).second.second == playerTwo) {
                tree.removeNode(i);
            }
            else {
                i++;
            }
        }

    }*/

    std::vector<std::pair<int,int>> teams;
    for (int i = 0; i < numPlayers/2; i++){
        KeyValuePair players = tree.removeMin();
        int playerOne = players.second.first, playerTwo = players.second.second;

        for(int i = 1; i < tree.returnSize()+1; i+=0) {
            if (tree.returnKvp(i).second.first == playerOne || tree.returnKvp(i).second.second == playerOne ||
                tree.returnKvp(i).second.first == playerTwo || tree.returnKvp(i).second.second == playerTwo) {
                tree.removeNode(i);
            }
            else {
                i++;
            }
        }

    }


    jsonPrint["teams"] = teams;
    std::cout << jsonPrint.dump(2);

}