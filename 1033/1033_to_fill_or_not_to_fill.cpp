#include <iostream> 
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

#include <stdio.h>
#include <string.h>

using namespace std;

struct GasStation
{
    double unit_price;
    double distance;
};

int main(int argc, char * const argv[])
{
    double C_max, D, D_avg;
    int N;
    cin >> C_max >> D >> D_avg >> N;

    vector<GasStation> stations(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> stations[i].unit_price >> stations[i].distance;
    }

    sort(stations.begin(), stations.end(), [](const GasStation &a, const GasStation &b) {
        return a.distance < b.distance;
    });

    if (D == 0)
    {
        cout << "0.00\n";
        return 0;
    }
    if (stations[0].distance != 0)
    {
        printf("The maximum travel distance = 0.00\n");
        return 0;
    }

    double cur_gas = 0;
    double cur_cost = 0;
    int cur_station = 0;

    int max_dist_full_tank = C_max * D_avg;  // 油箱加满油的能行驶的最大距离

    while (true)
    {
        bool has_station_in_range = false;  // 加满油最大行驶距离内是否有加油站
        bool has_cheaper_station = false;  // 最大行驶距离内是否有比当前加油站油价便宜的加油站
        double cheapest_price_in_range = std::numeric_limits<double>::max();
        int cheapest_station = -1;
        for (int i = cur_station + 1; i < N; ++i)
        {
            if (stations[i].distance - stations[cur_station].distance <= max_dist_full_tank)
            {
                has_station_in_range = true;
                if (stations[i].unit_price < stations[cur_station].unit_price)
                {
                    has_cheaper_station = true;

                    double dist = stations[i].distance - stations[cur_station].distance;
                    double gas_needed = dist / D_avg - cur_gas;
                    cur_cost += stations[cur_station].unit_price * gas_needed;

                    cur_gas = 0;
                    cur_station = i;
                    break;
                }

                if (stations[i].unit_price < cheapest_price_in_range)
                {
                    cheapest_price_in_range = stations[i].unit_price;
                    cheapest_station = i;
                }
            }
            else
                break;
        }

        if (!has_cheaper_station && D - stations[cur_station].distance <= max_dist_full_tank)
        {
            double dist = D - stations[cur_station].distance;
            double gas_needed = dist / D_avg - cur_gas;
            cur_cost += stations[cur_station].unit_price * gas_needed;

            printf("%.2lf\n", cur_cost);
            return 0;
        }

        if (has_station_in_range && !has_cheaper_station)
        {
            double gas_needed = C_max - cur_gas;
            cur_cost += stations[cur_station].unit_price * gas_needed;

            double dist = stations[cheapest_station].distance - stations[cur_station].distance;
            cur_gas = C_max - dist / D_avg;
            cur_station = cheapest_station;
        }
        else if (!has_station_in_range)
        {
            printf("The maximum travel distance = %.2lf\n", stations[cur_station].distance + max_dist_full_tank);
            return 0;
        }
    }

    return 0;
}
