package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
)

func main() {
	var ipS string = "10.146.202.50"
	var portS string = "42069"

	// fmt.Print("Please give server IP: ")
	// _, err := fmt.Scan(&ipS)
	//
	// if err != nil {
	// 	log.Fatal(err)
	// }
	//
	// fmt.Print("Please give server port: ")
	// _, err = fmt.Scan(&portS)
	//
	// if err != nil {
	// 	log.Fatal(err)
	// }

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
  scanner := bufio.NewScanner(os.Stdin)

	fmt.Println("Please write your message: ")

  //loop for each line the user puts and add it to message 
  for scanner.Scan() {
    scanned := scanner.Text() 
    if scanned == "" {
      break
    }
    message += scanned + "\n"
  }

  //10.146.202.50

	//send the message
	n, err := conn.Write([]byte(message))

  if (err != nil) {
    log.Fatal(err)
  } else {
    fmt.Printf("Sent %v to server\nMessage: %v\n", n, message)
  }
}
