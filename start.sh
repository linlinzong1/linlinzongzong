#!/bin/bash

PROJECT_DIR=$(pwd)

echo "Starting backend..."


cd $PROJECT_DIR/backend/build


./linlinzongzong & \
>>../../logs/backend.log \
2>&1 &


BACKEND_PID=$!


echo "Backend started, PID=$BACKEND_PID"


sleep 2


echo "Starting frontend..."


cd $PROJECT_DIR/frontend


npm run dev
