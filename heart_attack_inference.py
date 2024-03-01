import requests
import time
import datetime

def prevention_suite(trtbps, chol, thalachh):
    if chol > 500:
        return True
    elif trtbps > 200:
        return True
    elif thalachh > 190:
        return True
    else:
        return False
    
def update_data_to_json_link(url):
    try:
        # Send a PUT request with JSON data
        response = requests.get(url=url)

        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            print('[UPDATE LOG:] - UPDATE STATUS: OK!')
        else:
            print(f"Error: Unable to update data. Status code: {response.status_code}")
    except Exception as e:
        print(f"An error occurred: {e}")

def get_data_from_json_link(json_link):
    try:
        response = requests.get(json_link)
        if response.status_code == 200:
            json_data = response.json()
            return json_data
        else:
            print(f"Error: Unable to fetch data. Status code: {response.status_code}")
            return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None



while True:

    time.sleep(2)
    
    json_link_trtbps = "https://blr1.blynk.cloud/external/api/get?token=ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y&v16"

    json_data_trtbps = int(get_data_from_json_link(json_link_trtbps)) # updated value

    json_link_chol = "https://blr1.blynk.cloud/external/api/get?token=ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y&v9"
    json_data_chol = int(get_data_from_json_link(json_link_chol)) # updated value
        
    json_link_thalachh = "https://blr1.blynk.cloud/external/api/get?token=ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y&v14"
    json_data_thalachh = int(get_data_from_json_link(json_link_thalachh)) # updated value


    if prevention_suite(trtbps=json_data_trtbps, chol=json_data_chol, thalachh=json_data_thalachh) == True:
        response = 'You are heart attack positive'
    else: 
        response = 'You are heart attack negative'

    # Call the function to update data
    update_data_to_json_link(url = f"https://blr1.blynk.cloud/external/api/update?token=ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y&v6={response}")
