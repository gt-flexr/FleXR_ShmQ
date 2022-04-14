g++ -o element_test_client.out element_test_client.cc `pkg-config --libs --cflags flexr_shmq`
g++ -o element_test_server.out element_test_server.cc `pkg-config --libs --cflags flexr_shmq`
g++ -o part_element_test_client.out part_element_test_client.cc `pkg-config --libs --cflags flexr_shmq`
g++ -o part_element_test_server.out part_element_test_server.cc `pkg-config --libs --cflags flexr_shmq`

./element_test_client.out &
./element_test_server.out

./part_element_test_client.out &
./part_element_test_server.out


rm *.out
