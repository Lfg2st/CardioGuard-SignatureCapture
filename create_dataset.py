import mediapipe as mp 
import cv2 
import os 
import matplotlib.pyplot as plt 
import pickle

# Define the path to the "data" folder
data_folder = "/Users/anhadsinghnarang/Documents/SignatureCapture/data"


mp_hands = mp.solutions.hands 
hands = mp_hands.Hands(static_image_mode = True, min_detection_confidence=0.3)


data = []
labels = []

# Iterate over subfolders from 0 to 25
for folder_name in range(0, 26):
    folder_path = os.path.join(data_folder, str(folder_name))
    files = sorted(os.listdir(folder_path))

    for index, filename in enumerate(files):
       if index == 0:
           pass
       else:
           data_aux = []

           img = cv2.imread(os.path.join(folder_path, filename))
           img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
           results = hands.process(img_rgb)
           for hand_landmarks in results.multi_hand_landmarks:
               for i in range(len(hand_landmarks.landmark)):
                   x = hand_landmarks.landmark[i].x
                   y = hand_landmarks.landmark[i].y
                   data_aux.append(x)
                   data_aux.append(y)
           
           data.append(data_aux)  
           labels.append(folder_name)  
           print(f"{folder_name}/26")

f = open('data.pickle', 'wb')
pickle.dump({'data':data, 'labels':labels}, f)
f.close()
