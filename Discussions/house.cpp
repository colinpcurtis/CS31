#include <iostream> 
#include <string>
using namespace std;

int main() {
     string houseState;
     int housePrice = 0;
     int houseArea;
     int areaMultiplier;
     cout << "House location ";
     getline(cin, houseState);

     cout << "house area ";
     cin >> houseArea;

     if (houseState == "CA") {
          areaMultiplier = 120;
     } else {
          areaMultiplier = 100;
     }

     if (houseArea <= 10) {
          housePrice += houseArea * 80;
     } else if (houseArea > 10 && houseArea <= 20) {
          housePrice += 10 * 80;
          houseArea -= 10;
          housePrice += houseArea * areaMultiplier;
     } else if (houseArea > 20) {
          housePrice += 10 * 80 + 10 * areaMultiplier;
          houseArea -= 20;
          housePrice += 140 * houseArea;
     }
     cout << "house price: " << housePrice << endl;
}