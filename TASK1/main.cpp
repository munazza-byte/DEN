#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "json.hpp"
#include <algorithm>
#include <map>
using namespace std;
class Location 
{
    public:
    string name;
    double latitude;
    double longitude;
    Location()
    {

    }
    Location (string locaName,double lati,double longi):name(locaName),latitude(lati),longitude(longi) {

    }
    static vector<Location> Locations;
    void AddLocation(const Location& loca) 
    {
        Locations.push_back(loca);
    }
    static void ListTheLocations()
    {
        if(Locations.empty())
        {
            cout<<"No locations are available."<<endl;
        }
        else
        {
            for(const auto& loca : Locations) 
            {
                cout<<"Name: "<<loca.name<<"; Latitude: "<<loca.latitude<<"; Longitude: "<<loca.longitude<<endl;
            }
        }
    }
     static void RemoveALocation(const string& locaName) 
    {
        auto it=find_if(Locations.begin(),Locations.end(),[&](const Location& loca){return loca.name==locaName;});
        if(it != Locations.end())
        {
            Locations.erase(it);
            cout<<"Location "<< locaName <<" is removed successfully."<<endl;
        }
        else
        {
            cout<<"Location "<< locaName <<" not found."<<endl;
        }
    }

};
vector<Location> Location::Locations;
class WeatherVariable 
{
    private:
    map<string, double> variables;

    public:
    WeatherVariable() 
    {
        variables["wind_speed"]=12.5;
        variables["Temperature"] = 25.0;
        variables["Pressure"]=1013.0;
        variables["Humidity"] = 60.0;

    }

    // Define a new variable or overwrite an existing one
    void GetVariable(const string& key, double value) 
    {
        variables[key] = value;
        cout << "Variable '" << key << "' is defined successfully!" << endl;
    }

void UpdateVariable(const string& key) 
{
    auto it = variables.find(key);
    if (it != variables.end())
    {
        double value;
        cout << "Enter the new value for " << key << ": ";
        cin >> value;
        variables[key] = value;
        cout << key << " updated successfully!" << endl;
    }
    else
    {
        cout << "Variable '" << key << "' not found." << endl;
    }
}


void DisplayVariables() const 
{
    cout << "Currently defined variables are:\n";
    for (const auto& vari : variables) 
    {
        cout << vari.first << ": " << vari.second << endl;
    }
    if (variables.empty()) 
    {
        cout << "No variables are defined yet." << endl;
    }
}

};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) 
{
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}
class WeatherForecastingSystem 
{
    public:
    string fetchWeatherData(double latitude, double longitude) 
    {
        CURL* curl;
        string readBuffer;
        CURLcode ser;
        curl = curl_easy_init();
        if (curl) 
        {
            string url = "https://api.open-meteo.com/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&current_weather=true";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            ser = curl_easy_perform(curl);
            if (ser != CURLE_OK) 
            {
                cerr << "API request is failed: " << curl_easy_strerror(ser) << endl;
                return "";
            }
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }
    void displayWeatherData(double latitude,double longitude)
    {
        string Info=fetchWeatherData(latitude,longitude);
        cout<<"Weather Data for ("<<latitude<<", "<<longitude<<"):"<<Info<<endl;
    }
    void exportToCSV(const string& filename, const vector<string>& weatherData) 
    {
        ofstream file(filename);
        if (file) 
        {
            file << "Location,Latitude,Longitude,Temperature,Humidity,Pressure\n"; 
            for (const auto& Info : weatherData)
                file << Info << "\n";
            cout << "Information exported to " << filename << " (CSV)." << endl;
        } 
        else 
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
    void exportToJSON(const string& filename, const vector<pair<string, map<string, double>>>& weatherData) 
    {
        nlohmann::json jsonData;
        for (const auto& entry : weatherData)
            jsonData[entry.first] = entry.second;

        ofstream file(filename);
        if (file) 
        {
            file << jsonData.dump(4); 
            cout << "Data exported to " << filename << " (JSON)." << endl;
        } 
        else 
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};
class HistoricalWeatherSystem
{
    private:
    string ApiToken;

    public:
    HistoricalWeatherSystem(const string& key) : ApiToken(key) {}

    string fetchHistoricalWeatherData(const string& location)
    {
        return "{\"location\": \"" + location + "\",\"temperature\":15.0,\"wind_speed\":7.0}";
    }

    void displayHistoricalData(const string& location)
    {
        string Info = fetchHistoricalWeatherData(location);
        cout << "Historical Weather Data for " << location << ": " << Info << endl;
    }

    void exportHistoricalDataToJSON(const string& filename, const vector<pair<string, map<string, double>>>& historicalData) 
    {
        nlohmann::json jsonData;
        for (const auto& entry : historicalData)
        {
            jsonData[entry.first] = entry.second; 
        }
        ofstream file(filename);
        if (file.is_open()) 
        {
            file << jsonData.dump(4); 
            file.close();
            cout << "Historical data exported to " << filename << " successfully." << endl;
        } 
        else 
        {
            cerr << "Could not open the file for writing." << endl;
        }
    }
    void exportHistoricalDataToCSV(const string& filename, const vector<string>& historicalData) 
    {
        ofstream file(filename);
        if (file.is_open()) 
        {
            file << "Location,Latitude,Longitude,Date,Temperature,Pressure,wind_speed\n"; 
            for (const auto& Info : historicalData) 
            {
                file << Info << "\n"; 
            }
            file.close();
            cout << "Historical data is exported to " << filename << " successfully." << endl;
        } 
        else 
        {
            cerr << "Could not open the file for writing." << endl;
        }
    }

};
void DisplayTheMenu() 
{
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Manage Locations" << endl;
    cout << "2. Fetch and Export Weather Data" << endl;
    cout << "3. Manage Weather Variables " << endl;
    cout << "4. Fetch and Export Historical Weather Data" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void DisplayTheLocationMenu() 
{
    cout << "\n--- Manage The Locations ---" << endl;
    cout << "1. Add a new Location" << endl;
    cout << "2. List all Locations" << endl;
    cout << "3. Remove A Location " << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void DisplayTheWeatherMenu() 
{
    cout << "\n--- Manage The Weather Variables ---" << endl;
    cout << "1. Define a new Weather Variable" << endl;
    cout << "2. List all Weather Variables" << endl;
    cout << "3. Update A Weather Variable" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Location loca1("Lahore", 23.6844, 68.0479);
    Location loca2("Multan", 21.8607, 78.0011);
    loca1.AddLocation(loca1);
    loca1.AddLocation(loca2);
    WeatherVariable WeatherVari;
    WeatherForecastingSystem WeatherFSystem;
    HistoricalWeatherSystem HistoricalWSystem("YOUR_API_TOKEN");

    char Choice;
    do {
        DisplayTheMenu();
        cin >> Choice;
        cin.ignore();

        switch (Choice) {
            case '1': {
                char locaChoice;
                do {
                    DisplayTheLocationMenu();
                    cin >> locaChoice;
                    cin.ignore();

                    switch (locaChoice) {
                        case '1': {
                            string locaName;
                            double latitude, longitude;
                            cout << "Enter the name of the desired location: ";
                            getline(cin, locaName);
                            cout << "Enter the latitude: ";
                            cin >> latitude;
                            cout << "Enter the longitude: ";
                            cin >> longitude;
                            cin.ignore();
                            Location newLoca(locaName, latitude, longitude);
                            newLoca.AddLocation(newLoca);
                            cout << "\n The Desired Location is added successfully!" << endl;
                            break;
                        }
                        case '2': {
                            Location::ListTheLocations();
                            break;

                        }
                        case '3': {
                           string locaNameToDelete;
                           cout << "Enter the name of the location you desire to delete: ";
                           getline(cin, locaNameToDelete);
                           Location::RemoveALocation(locaNameToDelete);
                           break;
                        }
                    }
                } while (locaChoice != '4');
                break;
            }
            case '2': 
                {
                WeatherFSystem.displayWeatherData(loca1.latitude, loca1.longitude);

                vector<string> weatherData = {
                    "Lahore,23.6844,73.0479,29.0,11.0,1013.0",  
                    "Multan,21.7207,67.0011,32.0,9.0,1080.0"
                };
                WeatherFSystem.exportToCSV("weather_forecast.csv", weatherData);
                cout << "CSV export completed.\n";

                vector<pair<string, map<string, double>>> jsonData = {
                    {"Lahore", {{"Latitude", 23.6844}, {"Longitude", 73.0479}, {"Temperature", 29.0}, {"Humidity", 11.0},{"Pressure",1013.0}}},
                    {"Multan", {{"Latitude", 21.7207}, {"Longitude", 67.0011}, {"Temperature", 32.0}, {"Humidity", 9.0},{"Pressure",
1080.0}}}
                };
                WeatherFSystem.exportToJSON("weather_forecast.json", jsonData);
                cout << "JSON export completed.\n";

                break;
                }
                
            case '3': {
                char WChoice;
                    do {
                        DisplayTheWeatherMenu();
                        cin >> WChoice;
                        cin.ignore();
                        switch (WChoice) {
                            case '1': {
                                string key;
                                double value;
                                cout << "Enter the weather variable name: ";
                                getline(cin, key);
                                cout << "Enter the value: ";
                                cin >> value;
                                cin.ignore();

                                WeatherVari.GetVariable(key, value);
                                cout << "Variable defined successfully!" << endl;
                                break;
                            }
                            case '2': {
                                WeatherVari.DisplayVariables();
                                break;

                            }

                            case '3': {
                                 string key;
                                cout << "Enter the weather variable name to update: ";
                                getline(cin, key);

                                WeatherVari.UpdateVariable(key);
                                break;


                            }
                        }
                    } while (WChoice != '4');
                    break;
                }
               
            
            case '4': {
                HistoricalWSystem.displayHistoricalData("Lahore");
                HistoricalWSystem.displayHistoricalData("Multan");


                vector<string> historicalData = {
                    "Lahore,33.6844,73.0479,2022-03-01,26.0,1130.0,20.0",
                    "Multan,24.8607,67.0011,2022-11-01,28.0,1090.0,22.0"
                };
                HistoricalWSystem.exportHistoricalDataToCSV("historical_data.csv", historicalData);
                cout << "Historical data export to CSV completed.\n";


                vector<pair<string, map<string, double>>> historicalJsonData = {
                    {"Lahore", {{"Latitude", 33.6844}, {"Longitude", 73.0479}, {"Date", 20220301}, {"Temperature", 26.0}, {"Pressure", 1130.0},{"wind_speed",20.0}}},
                    {"Multan", {{"Latitude", 24.8607}, {"Longitude", 67.0011}, {"Date", 20221101}, {"Temperature", 28.0}, {"Pressure", 1090.0},{"wind_speed",22.0}}}
                };

                HistoricalWSystem.exportHistoricalDataToJSON("historical_data.json", historicalJsonData);
                cout << "Historical data export to JSON completed.\n";
            }
        }
    } while (Choice != '5');

    return 0;
}
