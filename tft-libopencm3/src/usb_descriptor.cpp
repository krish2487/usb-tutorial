/*
 * USB Tutorial
 * 
 * Copyright (c) 2020 Manuel Bleichenbacher
 * Licensed under MIT License
 * https://opensource.org/licenses/MIT
 * 
 * USB descriptor
 */

#include "usb_descriptor.h"

#define USB_VID 0xcafe        // Vendor ID
#define USB_PID 0xceaf        // Product ID
#define USB_DEVICE_REL 0x0061 // release 0.6.1

const char *const usb_desc_strings[] = {
    "Tutorial",          //  USB Manufacturer
    "Display",           //  USB Product
    "0004",              //  Serial number
    "Display Interface", //  Data interface
};

enum usb_strings_index
{ //  Index of USB strings.  Must sync with above, starts from 1.
    USB_STRINGS_MANUFACTURER_ID = 1,
    USB_STRINGS_PRODUCT_ID,
    USB_STRINGS_SERIAL_NUMBER_ID,
    USB_STRINGS_DATA_IF_ID,
};

static const struct usb_endpoint_descriptor comm_endpoint_descs[] = {
    {
        .bLength = USB_DT_ENDPOINT_SIZE,
        .bDescriptorType = USB_DT_ENDPOINT,
        .bEndpointAddress = EP_DATA_OUT,
        .bmAttributes = USB_ENDPOINT_ATTR_BULK,
        .wMaxPacketSize = BULK_MAX_PACKET_SIZE,
        .bInterval = 0,
        .extra = nullptr,
        .extralen = 0,
    },
};

static const struct usb_interface_descriptor comm_if_descs[] = {
    {
        .bLength = USB_DT_INTERFACE_SIZE,
        .bDescriptorType = USB_DT_INTERFACE,
        .bInterfaceNumber = INTF_COMM,
        .bAlternateSetting = 0,
        .bNumEndpoints = sizeof(comm_endpoint_descs) / sizeof(comm_endpoint_descs[0]),
        .bInterfaceClass = USB_CLASS_VENDOR,
        .bInterfaceSubClass = 0,
        .bInterfaceProtocol = 0, // vendor specific
        .iInterface = USB_STRINGS_DATA_IF_ID,
        .endpoint = comm_endpoint_descs,
        .extra = nullptr,
        .extralen = 0,
    },
};

static const struct usb_interface usb_interfaces[] = {
    {
        .cur_altsetting = nullptr,
        .num_altsetting = sizeof(comm_if_descs) / sizeof(comm_if_descs[0]),
        .iface_assoc = nullptr,
        .altsetting = comm_if_descs,
    },
};

const struct usb_config_descriptor usb_config_descs[] = {
    {
        .bLength = USB_DT_CONFIGURATION_SIZE,
        .bDescriptorType = USB_DT_CONFIGURATION,
        .wTotalLength = 0,
        .bNumInterfaces = sizeof(usb_interfaces) / sizeof(usb_interfaces[0]),
        .bConfigurationValue = 1,
        .iConfiguration = 0,
        .bmAttributes = 0x80, // bus-powered, i.e. it draws power from USB bus
        .bMaxPower = 0xfa,    // 500 mA
        .interface = usb_interfaces,
    },
};

const struct usb_device_descriptor usb_device_desc = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200, // USB version 2.00
    .bDeviceClass = USB_CLASS_VENDOR,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0, // no class specific protocol
    .bMaxPacketSize0 = BULK_MAX_PACKET_SIZE,
    .idVendor = USB_VID,
    .idProduct = USB_PID,
    .bcdDevice = USB_DEVICE_REL,
    .iManufacturer = USB_STRINGS_MANUFACTURER_ID,
    .iProduct = USB_STRINGS_PRODUCT_ID,
    .iSerialNumber = USB_STRINGS_SERIAL_NUMBER_ID,
    .bNumConfigurations = sizeof(usb_config_descs) / sizeof(usb_config_descs[0]),
};
