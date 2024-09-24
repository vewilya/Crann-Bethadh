
cd ui
npm run build
cd ..

mkdir build_release
cd build_release
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 ../..
cmake --build .
cd ..
