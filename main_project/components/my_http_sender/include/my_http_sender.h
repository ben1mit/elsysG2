#ifndef COMPONENTS_MY_HTTP_SENDER_H_
#define COMPONENTS_MY_HTTP_SENDER_H_



void http_sender_main(void);
void my_http_sender_init(); // call this function first. (unless you call http_sender_main)
void my_http_sender_send_turbine(int turbin_id, int data); // function for sending in our specific format.


#endif /* COMPONENTS_MY_HTTP_SENDER_H_ */