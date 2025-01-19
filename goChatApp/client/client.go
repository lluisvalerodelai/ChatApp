package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
	var ipS string = "127.0.0.1"
	var portS string = "42069"

	// fmt.Print("Please giv
	//now we have port & ip, we can connect via TCP to server and leave the connection open

	conn, err := net.Dial("tcp", ipS+":"+portS)
	defer conn.Close()

	if err != nil {
		fmt.Printf("failed to connect to %v:%v\n", ipS, portS)
		log.Fatal(err)
	} else {
		fmt.Printf("succesfully connected to %v:%v \n", ipS, portS)
	}

	//infinite loop of action until user disconnects
	var action string
	for {
		//promt for action
    fmt.Print("What would you like to do? \nn: Send a new message\nl: close connection\nAction:")
		_, err := fmt.Scan(&action)

		if err != nil {
			log.Fatal(err)
		}

		//act on action
		if action == "n" {
			sendMessage(conn)
		}

	}

}

func sendMessage(conn net.Conn) {
	//promt user for message
	var message string

	fmt.Println("Please write your message: ")
  _, err := fmt.Scan(&message)

  if (err != nil) {
    log.Fatal(err)
  }

	//send the message
	n, err := conn.Write([]byte(message))

  if (err != nil) {
    log.Fatal(err)
  } else {
    fmt.Printf("Sent %v to server\nMessage: %v\n", n, message)
  }
}
