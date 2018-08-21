intexit() {
    # Kill all subprocesses (all processes in the current process group)
    kill -HUP -$$
}

hupexit() {
    # HUP'd (probably by intexit)
    echo
    echo "Interrupted"
    exit
}

trap hupexit HUP
trap intexit INT

#================================================

./build/Debug/MockDist-Server &
./build/Debug/MockDist-Balancer &
./build/Debug/MockDist-Sink &

./build/Debug/MockDist-Worker &
./build/Debug/MockDist-Worker &
./build/Debug/MockDist-Worker &
./build/Debug/MockDist-Worker &

./build/Debug/MockDist-Worker &
./build/Debug/MockDist-Worker &
./build/Debug/MockDist-Worker &
./build/Debug/MockDist-Worker

#================================================

wait
