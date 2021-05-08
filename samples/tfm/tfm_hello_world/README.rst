.. _tfm_hello_world:

TF-M Hello World
################

.. contents::
   :local:
   :depth: 2

A simple sample based on Hello World that demonstrates adding Trusted Firmware-M (TF-M) to an application.

Overview
********

This sample uses the Platform Security Architecture (PSA) API to calculate a SHA-256 digest and the TF-M platform read service to read two FICR registers.
The PSA API call is handled by the TF-M secure firmware.

Requirements
************

The sample supports the following development kits:

.. table-from-rows:: /includes/sample_board_rows.txt
   :header: heading
   :rows: nrf5340dk_nrf5340_cpuappns, nrf9160dk_nrf9160ns

Building and Running
********************

.. |sample path| replace:: :file:`samples/tfm/tfm_hello_world`

.. include:: /includes/build_and_run.txt

Testing
=======

After programming the sample, the following output is displayed in the console:

.. code-block:: console

    Hello World! nrf5340dk_nrf5340_cpuapp
    Reading some secure memory that NS is allowed to read
    FICR->INFO.PART: 0x00005340
    FICR->INFO.VARIANT: 0x514b4141
    Hashing 'Hello World! nrf5340dk_nrf5340_cpuapp'
    SHA256 digest:
    12f0c84eecba8497cc0bec1ebc5a785d
    f2ae027a2545921d6cdc0920c5aaefd7

Dependencies
*************

This sample uses the TF-M module that can be found in the following location in the |NCS| folder structure:

* ``modules/tee/tfm/``

This sample uses the following libraries:

* :ref:`lib_tfm_ioctl_api`
