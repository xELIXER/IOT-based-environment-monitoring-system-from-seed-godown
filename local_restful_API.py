from bottle import run, get
import pymongo
import datetime
import socket

#To get the IP address
hostname = socket.gethostname()   
IPAddr = socket.gethostbyname(hostname)   

#MongoDB creds
client = pymongo.MongoClient()
db = client.tempdb

#Request are defined below
@get('/<temp>')
def checkTemp(temp):
    #Time variable
    now = datetime.datetime.now()
    print temp
    current_time = now.strftime("%d-%m-%Y %H-%M-%S")
    if temp<25 or temp>30:
        db.mycol.insert({"temp" : temp,"time": current_time})
        return({"temp" : temp,"time": current_time})

run(host=IPAddr, port=8080,reloader=True, debug=True)