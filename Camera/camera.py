import cv2
import numpy as np

def center_y(cnt):
    try:
        mm = cv2.moments(cnt)
        cx = int(mm['m10'] / mm['m00'])
        cy = int(mm['m01'] / mm['m00'])
        if cy < 200 or cx < 50 or cx > 600:
            cy = 99999
        return cy
    except ZeroDivisionError:
        return 999999

cap = cv2.VideoCapture(1)
while cap.isOpened():
    ok, frame = cap.read()
    if not ok:
        break
    frame = frame[:, 0:320]
    size = frame.shape[::-1]
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    #hsv = cv2.erode(hsv, None, iterations=2)
    out = cv2.inRange(hsv, (0,0,150), (180,30,255))
    #轮廓检测
    binary = cv2.Canny(out, 50, 150)
    cnts, hierarchy = cv2.findContours(out, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for cnt in range(len(cnts)):
        # 提取与绘制轮廓
        cv2.drawContours(frame, cnts, cnt, (0, 255, 0), 2)
        try:
            mm = cv2.moments(cnts[cnt])
            cx = int(mm['m10'] / mm['m00'])
            cy = int(mm['m01'] / mm['m00'])
            cv2.circle(frame, (cx, cy), 3, (0, 0, 255), -1)
        except ZeroDivisionError:
            pass
    try:
        #c = max(cnts, key=cv2.contourArea)
        c = min(cnts, key=center_y)
        rect = cv2.minAreaRect(c)
        box = cv2.boxPoints(rect)
        cv2.drawContours(frame, [np.int0(box)], -1, (0,255,255), 2)
    except ValueError:
        print("not found!")
    #显示输出
    cv2.imshow("output", frame)
    c = cv2.waitKey(10)
    if c & 0xFF == ord('q'):
        break
# 释放摄像头并销毁所有窗口
cap.release()
cv2.destroyAllWindows()