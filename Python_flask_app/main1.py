import thing
from importlib import import_module
import os
from flask import Flask, render_template, Response
from flask import *
from skimage.io import imread, imsave
from skimage.color import rgb2gray, rgb2grey
from skimage.color import rgb2hsv
from skimage import data
# import camera driver
if os.environ.get('CAMERA'):
    Camera = import_module('camera_' + os.environ['CAMERA']).Camera
else:
    from camera import Camera


# Create flask app and global pi 'thing' object.
app = Flask(__name__)
pi_thing = thing.PiThing()




# Define app routes.
# Index route renders the main HTML page.
@app.route("/")



def index():
    # Read the current switch state to pass to the template.
    inp_image = imread('/home/pi/image111.png')
    y = inp_image.mean()
    switch = y
    # Render index.html template.
    return render_template('index2.html', switch=switch)
def gen(camera):
    """Video streaming generator function."""
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

# LED route allows changing the LED state with a POST request.
@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')
                    
@app.route('/left_side')
def left_side():
    data1 = "LEFT"
    GPIO.output(m11 , 0)
    GPIO.output(m12 , 0)
    GPIO.output(m21 , 1)
    GPIO.output(m22 , 0)
    return 'true'
@app.route('/right_side')
def right_side():
   data1 = "RIGHT"
   pi_thing.set_led(1)
   return 'true'
@app.route('/up_side')
def up_side():
   data1 = "FORWARD"
   pi_thing.set_led(1)
   
   
   
   return 'true'
@app.route('/down_side')
def down_side():
   data1 = "BACK"
  
   
   return 'true'
@app.route('/stop')
def stop():
   data1 = "STOP"
   
   
   return  'true'

@app.route("/led/<int:state>", methods=['POST'])
def led(state):
    # Check if the led state is 0 (off) or 1 (on) and set the LED accordingly.
    if state == 0:
        pi_thing.set_led(0)
    elif state == 1:
        pi_thing.set_led(1)
    else:
        return ('Unknown LED state', 400)
    return ('', 204)


# Start the flask debug server listening on the pi port 5000 by default.
if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True, threaded=True)
