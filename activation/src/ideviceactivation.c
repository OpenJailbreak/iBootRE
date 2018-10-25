/*
 * iphoneactivation.c
 * A simple utility to handle the activation process for iPhones
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <glib.h>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

enum cmd_mode {
	CMD_ACTIVATE,
	CMD_DEACTIVATE,
	CMD_HACKTIVATE
};

static lockdownd_client_t client = NULL;
static idevice_t phone = NULL;

static void buffer_read_from_filename(const char *filename, char **buffer, uint32_t *length)
{
	FILE *f;
	uint64_t size;

	f = fopen(filename, "rb");

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	rewind(f);

	*buffer = (char*)malloc(sizeof(char)*size);
	if(fread(*buffer, sizeof(char), size, f) != size) {
		printf("Unable to read %llu bytes from '%s'.\n", size, filename);
		free(*buffer);
		*buffer = NULL;
	}
	fclose(f);

	*length = size;
}

static int plist_read_from_filename(plist_t *plist, const char *filename)
{
	char *buffer = NULL;
	uint32_t length;

	if (!filename)
		return 0;

	buffer_read_from_filename(filename, &buffer, &length);

	if (!buffer) {
		return 0;
	}

	if (memcmp(buffer, "bplist00", 8) == 0) {
		plist_from_bin(buffer, length, plist);
	} else {
		plist_from_xml(buffer, length, plist);
	}

	free(buffer);

	return 1;
}

static void print_usage(int argc, char **argv)
{
	char *name = NULL;

	name = strrchr(argv[0], '/');
	printf("Usage: %s [OPTIONS] CMD\n", (name ? name + 1: argv[0]));
	printf("Activate or Deactivate an iPhone device .\n\n");
	printf("commands:\n");
	printf("  activate\tAttempts to activate device contacting Apple\n");
	printf("  hacktivate\tHacktivates a jailbroken device (fake activation)\n");
	printf("  deactivate\tResets device to state prior to activation\n\n");
	printf("  -d, --debug\t\tenable communication debugging\n");
	printf("  -u, --uuid UUID\ttarget specific device by its 40-digit device UUID\n");
	printf("  -h, --help\t\tprints usage information\n");
	printf("\n");
	printf("\n");
}

int main(int argc, char *argv[])
{
	idevice_error_t ret = IDEVICE_E_UNKNOWN_ERROR;
	int i;
	char uuid[41];
	int cmd = -1;
	uuid[0] = 0;

	/* parse cmdline args */
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")) {
			idevice_set_debug_level(1);
			continue;
		}
		else if (!strcmp(argv[i], "-u") || !strcmp(argv[i], "--uuid")) {
			i++;
			if (!argv[i] || (strlen(argv[i]) != 40)) {
				print_usage(argc, argv);
				return 0;
			}
			strcpy(uuid, argv[i]);
			continue;
		}
		else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			print_usage(argc, argv);
			return 0;
		}
		else if (!strcmp(argv[i], "activate")) {
			cmd = CMD_ACTIVATE;
		}
		else if (!strcmp(argv[i], "hacktivate")) {
			cmd = CMD_HACKTIVATE;
		}
		else if (!strcmp(argv[i], "deactivate")) {
			cmd = CMD_DEACTIVATE;
		}
		else {
			print_usage(argc, argv);
			return 0;
		}
	}

	/* verify options */
	if (cmd == -1) {
		printf("No command specified.\n");
		print_usage(argc, argv);
		return -1;
	}

	if (uuid[0] != 0) {
		ret = idevice_new(&phone, uuid);
		if (ret != IDEVICE_E_SUCCESS) {
			printf("No device found with uuid %s, is it plugged in?\n", uuid);
			return -1;
		}
	}
	else
	{
		ret = idevice_new(&phone, NULL);
		if (ret != IDEVICE_E_SUCCESS) {
			printf("No device found, is it plugged in?\n");
			return -1;
		}
	}

	if (LOCKDOWN_E_SUCCESS != lockdownd_client_new_with_handshake(phone, &client, "iphoneactivation")) {
		idevice_free(phone);
		return -1;
	}

	/* TODO: verify we got a device with SIM support */

	/* process command */
	switch(cmd) {
	case CMD_HACKTIVATE:
		/* TODO: are we activated already? */
		/* TODO: verify if we got a SIM inserted */
		printf("ERROR: Not implemented.\n");
	break;
	case CMD_ACTIVATE:
		/* TODO: verify if we got a SIM inserted */
/*
    uid = x.get_value("UniqueDeviceID")
    imei = x.get_value("InternationalMobileEquipmentIdentity")
    iccid = x.get_value("IntegratedCircuitCardIdentity")
    activation_info = x.get_value("ActivationInfo")
    serial_number = x.get_value("SerialNumber")
    imsi = x.get_value("InternationalMobileSubscriberIdentity")
    
    #p uid
    #p imei
    #p iccid
    #puts activation_info.to_plist
    #p serial_number
        
    #abort
    
    url = URI("https://albert.apple.com/WebObjects/ALActivation.woa/wa/iPhoneRegistration")
 
    http = Net::HTTP.new(url.host, url.port)
 
    http.use_ssl = true
 
    http.start do |h|
      req = Net::HTTP::Post.new(url.path, "User-Agent" => "iTunes/7.7 (Macintosh; U; Intel Mac OS X 10.5.4)")
 
      req.form_data = {
        "AppleSerialNumber" => serial_number,
        "IMSI" => imsi,
        "InStoreActivation" => "false",
        "machineName" => "macos",
        "activation-info" => activation_info.to_plist,
        "ICCID" => iccid,
        "IMEI" => imei
      }
 
      #puts req.body
 
      result = h.request(req)
 
      puts result.body
 
      document = REXML::Document.new(result.body)
      
      activation = OSX.load_plist(document.root.elements[1].elements[1].to_s)
      
      pp activation
      
      activation_record = activation["iphone-activation"]["activation-record"]
      
      x.activate(activation_record)
*/
		printf("Creating activation record.\n");
		plist_t activation_record = NULL;
		plist_read_from_filename(&activation_record, "activation.plist");

		printf("Activating device... ");
		ret = lockdownd_activate(client, activation_record);
		if (ret == LOCKDOWN_E_SUCCESS)
			printf("SUCCESS\n");
		else
			printf("FAILED. ERROR CODE: %d\n", ret);
		break;
		plist_free(activation_record);
		activation_record = NULL;
	case CMD_DEACTIVATE:
		printf("Deactivating device... ");
		ret = lockdownd_deactivate(client);
		if (ret == LOCKDOWN_E_SUCCESS)
			printf("SUCCESS\n");
		else
			printf("FAILED. ERROR CODE: %d\n", ret);
	break;
		default:
	break;
	}

	lockdownd_client_free(client);
	idevice_free(phone);

	return 0;
}

