#Sari Stissi
#Assignment 3
#Worked with Laurence


from time import time
import threading
from random import randint
# Thread 1 is sender
# Thread 2 is receiver
class BooleanComp():
    def __init__(self, startState):
        #initialize the value
        self._val = startState

    def __equals__(self, otherThing):
        #prints if two things are equal in comparison
        return self._val == otherThing

    def __notEqual__(self, otherThing):
        #prints if two things are not equal in comparison
        return self._val != otherThing

    def changeValue(self, newVal):
        self._val = newVal

#Variables needed for the sliding window
isFinished =  BooleanComp(False)
windowSize = 5
timeoutBase = 5
actualTimeout = timeoutBase*1
randomStartVal = 0
randomEndVal = 50
queueDataTransfer = []

#add the data to the queue if successfully sent
#chaotically choose if the packet will be lost or not
def chaoticAddToQueue(data, qTarget=queueDataTransfer):
    randomChange = randint(randomStartVal, randomEndVal)
    writeToQueue = BooleanComp(True)
    if randomChange == 0:
        write.changeValue(False)
        print("The Packet was chaotically lost.")
    elif randomChange == 1:
        data["checksum"] += 1
        print("The checksum was increased.")
    elif randomChange == 2:
        data["checksum"]
        print("The checksum was decreased.")
    else:
        print("There was no change in the sequence.", data["seq"])\
    if writeToQueue == True:
        qTarget.append(data)

def functionSort(data):
    return data["seq"]

def receiverThread(lock):
    print("The receiver thread has begun.")
    currentData = {}
    while isFinished == False:
        currentFrame = 0
        if len(queueDataTransfer) > 0:
            lock.acquire()
            while currentFrame < len(queueDataTransfer):
                temp = queueDataTransfer[currentFrame]
                if temp["checksum"] == len(temp["data"]) and temp["ack"] != True:
                    queueDataTransfer[currentFrame]["ack"] = true
                    currentFrame += 1
                    print("The data was received.\n Here's the current amount of data: ", len(currentData))
                else:
                    del queueDataTransfer[currentFrame]
                currentData[temp["seq"]] = temp
            lock.release()
    listOfData = []
    for i in currentData.keys():
        listOfData.append(currentData[i])
    sortedList = listOfData.sort(key=functionSort)
    print(listOfData,"\n",sortedList)


def senderThread(data, lock):
    print("The sender thread has begun")
    counter = 0
    windowStart = 0
    #below is a dict of dicts
    #the format is [sequence: {target: <frame>, timeout: <timestamp>}]
    buffer = []
    while counter < len(data) or len(data) != 0:
        lock.acquire()
        if len(queueDataTransfer) < windowSize and windowStart <= counter < windowStart + windowSize and counter < len(data):
            print("Adding to the transfer queue.")
            chaoticAddToQueue(data[counter])
            buffer.append({"target":data[x], "timeout":time()+actualTimeout})
            counter += 1
        lock.release()

        for i in range(len(buffer)):
            lock.acquire()
            currentTime = time()
            if buffer[i]["timeout"] <= currentTime:
                print("The Packet timed out")
                chaoticAddToQueue(buffer[i]["target"])
                buffer[i]["timeout"] = currentTime + actualTimeout
            lock.release()

        lock.acquire()
        lengthOfQueue = len(queueDataTransfer)
        for queueDataIndex in range(len(queueDataTransfer)):
            if queueDataTransfer[queueDataIndex]["ack"] == True:
                tempPop = queueDataTransfer.pop(queueDataIndex)
                for j in range(len(buffer)):
                    if buffer[y]["target"]["seq"] == tem["seq"]:
                        if temp["seq"] == windowStart:
                            windowStart += 1
                        buffer.pop(y)
                        break
            if lengthOfQueue != len(queueDataTransfer):
                break
        lock.release()
    isFinished.changeValue(True)

def packagingData(fileName):
    formatedData = []
    with open(fileName, "r") as openFile:
        lineRead = openFile.readlines()
        for i in range(len(lineRead)):
            formatedData.append({"seq": i, "kind": "data", "ack": False, "data": lineRead[i], "checksum": len(lineRead[i])})
    return formatedData        
