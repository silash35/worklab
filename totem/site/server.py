from flask import Flask
from flask import request
from flask.templating import render_template
import os
import json

app = Flask(__name__)


def list_users():
    users = os.listdir('./templates/users')
    return users


@app.route('/')
def index():
    return render_template('index.html', users=list_users(), script=True)


@app.route('/users')
def get_users():
    return '%d' % len(list_users())

@app.route('/postmethod', methods = ['POST'])
def get_post_javascript_data():
    jsdata = request.form['javascript_data']
    print(jsdata)
    return jsdata

if __name__ == '__main__':
    app.run(host='0.0.0.0')
