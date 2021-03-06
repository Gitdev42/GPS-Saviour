/**
 * NeedyClient.h
 * Purpose: defines class NeedyClient
 *
 * @author Wall.Of.Death
 * @version 1.0
 */

#ifndef NeedyClient_H
#define NeedyClient_H

#include <iostream>
#include "Types.h"
#include "GPSAgent.h"
#include "GSMAgent.h"
#include "Timer.h"

using namespace std;

/**
 * @brief The NeedyClient class
 */
class NeedyClient {
    public:
        /* --- constructors / destructors --- */
        NeedyClient() {};

        /* --- initialization / main execution function --- */
        void init();
        void execute();

        /* --- getters / setters --- */
        bool getAuthIsRequired() const;
        void setAuthIsRequired(bool val_);

        StoringStatus getStoringStatus() const;
        void setStoringStatus(const StoringStatus &val_);

        SendingStatus getSendingStatus() const;
        void setSendingStatus(const SendingStatus &val_);

        int getRequestedDataArrayStartTime() const;
        void setRequestedDataArrayStartTime(int val_);

        int getRequestedDataArrayEndTime() const;
        void setRequestedDataArrayEndTime(int val_);

        int getSendingTimerInterval() const;
        void setSendingTimerInterval(int val_);

        int getStoringTimerInterval() const;
        void setStoringTimerInterval(int val_);

        int getContinouslySendingFinishedUntilTime() const;
        void setContinouslySendingFinishedUntilTime(int val_);

private:
        /* --- class member variables --- */
        GPSAgent gpsAgent;
        GSMAgent gsmAgent;
        Timer storingTimer;
        Timer sendingTimer;
        int sendingTimerInterval;
        int storingTimerInterval;

        bool authIsRequired;
        StoringStatus storingStatus;
        SendingStatus sendingStatus;

        int requestedDataArrayStartTime;
        int requestedDataArrayEndTime;

        // all values with a time before this time are already sent during sendingStatus=sendContinuously
        // all values with a time after this time are were not sent yet by sendingStatus=sendContinuously
        int continouslySendingFinishedUntilTime;

        /* --- main execution functions --- */
        void checkReveivedInitialization();
        bool checkReceivedRequestForStatusChange();
        void processTasks();
        void sendRequestForAuth();
        bool checkReceivedAuthPackage();
        bool checkTimeoutIsUp();
        bool checkAuthCompleted();
        void sendErrorPackage(const string& errorText_);
        void saveRequestedStatus();

        /* --- sub execution functions --- */
        void storeGPSData();
        void storeData();
        void sendData();

};

#endif // NeedyClient_H
