
cd ui
npm run build
cd ..

cd build/M1
cmake ../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 ../..
cmake --build .
cd ../..
