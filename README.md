# Arduino-home-monitoring-with-NagiosXI

All you need is:

  - An arduino (runs on an Arduino UNO)
  - An Ethernet Shield for your arduino
  - Some sensors: A motion sensor, temp & humidity sensor (like the DHT11), and so on...
  - Nagios XI (see my Docker container for a quick setup: https://hub.docker.com/r/tgoetheyn/docker-nagiosxi/)

customize the script with your appropiate IP adresses and NRDP key (found under "Configuring Inbound Checks")

You can use the wizard in Nagios XI to create a "Passive check"
Make shure the name is the same like you're using in the arduino script.

NOTE: because i don 't load the Ethernet server component in the arduino, you won't be able to ping it.
      You can check the Nagios XI event log to check if you recieve the NRDP check correctlly

Happy monitoring!
