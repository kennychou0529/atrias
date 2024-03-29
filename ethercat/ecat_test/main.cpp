#include "main.h"

void sig_handler(int signum) {
	done = true;
}

int main(int argc, char ** argv) {
	signal(SIGINT, sig_handler);
	ec_master_t* ec_master = ecrt_request_master(0);
	if (ec_master == NULL) {
		perror("ecrt_request_master failed.");
		return 1;
	}
	ec_domain_t* domain = ecrt_master_create_domain (ec_master);
	if (domain == NULL) {
		perror("ecrt_master_create_domain failed.");
		ecrt_release_master(ec_master);
		return 2;
	}
	
	ec_slave_config_t* sc0 = ecrt_master_slave_config(ec_master, 0, 0, VENDOR_ID, PRODUCT_CODE);
	
	if (ecrt_slave_config_pdos(sc0, 4, slave_0_syncs)) {
		perror("ecrt_slave_config_pdos() failed.");
		ecrt_release_master(ec_master);
		return 3;
	}
	
	unsigned int command_off;
	unsigned int input_counter_off;
	unsigned int ID_off;
	unsigned int state_off;
	unsigned int output_counter_off;
	unsigned int error_flags_off;
	unsigned int rot_x_off;
	unsigned int rot_y_off;
	unsigned int rot_z_off;
	unsigned int accel_x_off;
	unsigned int accel_y_off;
	unsigned int accel_z_off;
	unsigned int status_off;
	unsigned int sequence_off;
	unsigned int temp_off;
	unsigned int crc_off;
	ec_pdo_entry_reg_t entry_regs[] = { 
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 1,  &command_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x6, 1,  &input_counter_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 2,  &ID_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 3,  &state_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 4,  &output_counter_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 5,  &error_flags_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x8, 1,  &rot_x_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x8, 2,  &rot_y_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x8, 3,  &rot_z_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x8, 4,  &accel_x_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x8, 5,  &accel_y_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x8, 6,  &accel_z_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 6,  &status_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x5, 7,  &sequence_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x3, 1,  &temp_off, NULL},
		{0, 0, VENDOR_ID, PRODUCT_CODE, 0x7, 1,  &crc_off, NULL},
		{0, 0,      0x00,         0x00, 0x0, 0x0,           NULL, NULL}
	};
	if (ecrt_domain_reg_pdo_entry_list(domain, entry_regs)) {
		perror("ecrt_domain_reg_pdo_entry_list() failed");
		ecrt_release_master(ec_master);
		return 4;
	}
	if (ecrt_master_activate(ec_master)) {
		perror("ecrt_master_activate() failed");
		ecrt_release_master(ec_master);
		return 5;
	}

	uint8_t* domain_pd = ecrt_domain_data(domain);
	
	unsigned char* command       = (unsigned char*) (domain_pd + command_off);
	uint16_t*      input_counter = (uint16_t*)      (domain_pd + input_counter_off);
	uint8_t*       ID            = (uint8_t*)      (domain_pd + ID_off);
	uint8_t*       state         = (uint8_t*)      (domain_pd + state_off);
	uint8_t*       counter       = (uint8_t*)      (domain_pd + output_counter_off);
	uint8_t*       error_flags   = (uint8_t*)      (domain_pd + error_flags_off);
	float*         rot_x         = (float*  )      (domain_pd + rot_x_off);
	float*         rot_y         = (float*  )      (domain_pd + rot_y_off);
	float*         rot_z         = (float*  )(domain_pd + rot_z_off);
	float*         accel_x       = (float*  )      (domain_pd + accel_x_off);
	float*         accel_y       = (float*  )      (domain_pd + accel_y_off);
	float*         accel_z       = (float*  )      (domain_pd + accel_z_off);
	uint8_t*       status        = (uint8_t*)      (domain_pd + status_off);
	uint8_t*       sequence      = (uint8_t*)      (domain_pd + sequence_off);
	int16_t*       temp          = (int16_t*)      (domain_pd + temp_off);
	uint32_t*      crc           = (uint32_t*)     (domain_pd + crc_off);
	
	(*command) = 0;
	char input;
		timespec cur_time;
	clock_gettime(CLOCK_REALTIME, &cur_time);
	ecrt_master_application_time(ec_master, EC_NEWTIMEVAL2NANO(cur_time));
	ecrt_slave_config_dc(sc0, 0x0300, LOOP_PERIOD_NS, LOOP_PERIOD_NS - (cur_time.tv_nsec % LOOP_PERIOD_NS), 0, 0);
	
	long tgt_time = cur_time.tv_nsec;
	timespec wait_time = {
		0,
		0
	};
	ec_master_state_t master_state;
	
	*input_counter = 0;
	int  count = 0;
	while (!done) {
		// Set command input. TODO(yoos): The counter was meant to reset the Medulla state before setting it to run, but it's useless due to the delay between the EtherCAT PREOP and OP states.
		if ((count) <10) {
			*command = 6;   // Reset
			count++;
		}
		else
			*command = 2;   // Run
		(*input_counter) = (*input_counter)+1;

		clock_gettime(CLOCK_REALTIME, &cur_time);
		ecrt_master_application_time(ec_master, EC_NEWTIMEVAL2NANO(cur_time));
		ecrt_master_sync_reference_clock(ec_master);
		ecrt_master_sync_slave_clocks(ec_master);
		ecrt_domain_queue(domain);
		ecrt_master_send(ec_master);
		usleep(300);
		ecrt_master_receive(ec_master);
		ecrt_domain_process(domain);

		// Count number of errors
		static uint16_t seq_err_count = 0;
		seq_err_count += *error_flags & (1<<0);
		printf("%5u, ", seq_err_count);

		//printf("counter: %3d eflags: %2x Stat: %2x Seq: %3u Temp: %u RX: %+.20f RY: %+.20f RZ: %+.20f AX: %+.20f AY: %+.20f AZ: %+.20f CRC: %08x\n",*counter, *error_flags, *status, *sequence, *temp, *rot_x, *rot_y, *rot_z, *accel_x, *accel_y, *accel_z, *crc);

		// CSV
		printf("%3d, %2x, %2x, %3u, %u, %+.20f, %+.20f, %+.20f, %+.20f, %+.20f, %+.20f, %08x\n", *counter, *error_flags, *status, *sequence, *temp, *rot_x, *rot_y, *rot_z, *accel_x, *accel_y, *accel_z, *crc);

		// Visual sequence counter
		//int vis_counter;
		//for (vis_counter=0; vis_counter<*sequence; vis_counter++) {
		//	printf(".");
		//}
		//printf("\n");

		wait_time.tv_nsec = LOOP_PERIOD_NS - (cur_time.tv_nsec % LOOP_PERIOD_NS);
		if (*status != 0x77 && *status != 0) {
			printf("\n%x %x %x %x\n\n", *status, *sequence, *temp, *crc);
		}
		nanosleep(&wait_time, NULL);
	}
	
	ecrt_release_master(ec_master);
	return 0;
}
