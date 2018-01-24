/**
 * GPSAgent.cpp
 * Purpose: implements class GPSAgent
 *
 * @author TODO2
 * @version 1.0
 */

#include "../include/GPSAgent.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif


/* --- getters / setters --- */
void GPSAgent::setConnectionEstablished(bool val_) {
    connectionEstablished = val_;
}

bool GPSAgent::getConnectionEstablished() {
    return connectionEstablished;
}

GPSAgent::GPSAgent() {
    setConnectionEstablished(false);
    init();
}

bool GPSAgent::init() {
    if (! getConnectionEstablished()) {
        setConnectionEstablished(true);
        cout << "initialized GPSAgent" << endl;
    }
    return getConnectionEstablished();
}

/**
 * GPSAgent::receiveGeoData
 * @brief receives and stores geo-data from gps-sensor
 * @return true if GPSAgent was able to receive and store data
 *
 * This function does bla bla bla bla
 * bla bla bla bla
 * bla bla bla bla
 * bla bla bla bla
 * bla bla bla bla
 * bla bla bla bla
 */
bool GPSAgent::receiveGeoData() {
    if (init()){
        GeoData receivedData;
        if (testRecievedData()){
            receivedData = convertReceivedDataIntoGeoData();
            saveGeoData(receivedData);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/**
 * @brief GPSAgent::saveGeoData
 * @param receivedData_
 */
void GPSAgent::saveGeoData(GeoData receivedData_) {
    cout << "GeoData Dummy received" << endl;
    storedGeoData.push_back(receivedData_);
}

void GPSAgent::receiveDataFromGPSChip() const {
    cout << "Received Data From GPS Chip" << endl;
}

bool GPSAgent::testRecievedData()
{
   return true;
}

GeoData GPSAgent::convertReceivedDataIntoGeoData() const {
    GeoData geoD;
    /* initialize random seed: */
    srand (time(NULL));
    double noise = rand() % 100 + 1;
    noise = noise / 100.0;
    geoD.setHeight(5 + noise);
    geoD.setLatitude(54.382868 + noise);
    geoD.setLongitude(10.955257 + noise);
    geoD.setCTime(getTimeMs64());
    return geoD;
}

/**
 *
 * Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
 * windows and linux.
 * @source https://stackoverflow.com/questions/1861294/how-to-calculate-execution-time-of-a-code-snippet-in-c
 */

unsigned int GPSAgent::getTimeMs64() const {
#ifdef _WIN32
 /* Windows */
 FILETIME ft;
 LARGE_INTEGER li;

 /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
  * to a LARGE_INTEGER structure. */
 GetSystemTimeAsFileTime(&ft);
 li.LowPart = ft.dwLowDateTime;
 li.HighPart = ft.dwHighDateTime;

 uint64 ret = li.QuadPart;
 ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
 ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

 return ret;
#else
 /* Linux */
 struct timeval tv;

 gettimeofday(&tv, NULL);

 unsigned int ret = tv.tv_usec;
 /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
 ret /= 1000;

 /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
 ret += (tv.tv_sec * 1000);

 return ret;
#endif
 }
