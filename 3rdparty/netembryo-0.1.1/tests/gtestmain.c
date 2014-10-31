/* Generated by genmain.awk */
 #include <glib.h>
 
 int main(int argc, char *argv[])
 {
     g_test_init(&argc, &argv, NULL);

extern void test_local_hostname();
g_test_add_func("/test_hostname/local_hostname", test_local_hostname);
extern void test_connect_lscube();
g_test_add_func("/test_sock/connect_lscube", test_connect_lscube);
extern void test_flags_lscube();
g_test_add_func("/test_sock/flags_lscube", test_flags_lscube);
extern void test_local_port_lscube();
g_test_add_func("/test_sock/local_port_lscube", test_local_port_lscube);
extern void test_remote_host_lscube();
g_test_add_func("/test_sock/remote_host_lscube", test_remote_host_lscube);
extern void test_remote_port_lscube();
g_test_add_func("/test_sock/remote_port_lscube", test_remote_port_lscube);
extern void test_socket_pair_backwards();
g_test_add_func("/test_sock/socket_pair_backwards", test_socket_pair_backwards);
extern void test_socket_pair_crosstalk();
g_test_add_func("/test_sock/socket_pair_crosstalk", test_socket_pair_crosstalk);
extern void test_socket_pair_forwards();
g_test_add_func("/test_sock/socket_pair_forwards", test_socket_pair_forwards);
extern void test_type_lscube();
g_test_add_func("/test_sock/type_lscube", test_type_lscube);
extern void test_just_host();
g_test_add_func("/test_url/just_host", test_just_host);
extern void test_just_proto_host();
g_test_add_func("/test_url/just_proto_host", test_just_proto_host);
extern void test_just_proto_host_port();
g_test_add_func("/test_url/just_proto_host_port", test_just_proto_host_port);
extern void test_long_url();
g_test_add_func("/test_url/long_url", test_long_url);
extern void test_no_path();
g_test_add_func("/test_url/no_path", test_no_path);
extern void test_no_proto();
g_test_add_func("/test_url/no_proto", test_no_proto);
extern void test_split_url();
g_test_add_func("/test_url/split_url", test_split_url);

    return g_test_run();
 }
