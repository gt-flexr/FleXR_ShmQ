g++ -g -o element_test_client.out element_test_client.cc `pkg-config --libs --cflags flexr_shmq`
g++ -g -o element_test_server.out element_test_server.cc `pkg-config --libs --cflags flexr_shmq`
g++ -g -o part_element_test_client.out part_element_test_client.cc `pkg-config --libs --cflags flexr_shmq`
g++ -g -o part_element_test_server.out part_element_test_server.cc `pkg-config --libs --cflags flexr_shmq`

./element_test_client.out &
sleep 1
./element_test_server.out

./part_element_test_client.out &
sleep 1
./part_element_test_server.out


rm *.out
