package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
  //open server (binds to port automatically!!)
  addressFull := "127.0.0.1" + ":" + "42069"
  ln, err := net.Listen("tcp", addressFull)
  defer ln.Close()

  if (err != nil) {
    log.Fatal(err)
  }

  for {

    //accept new connection
    fmt.Println("listening for new connections...")
    conn, err := ln.Accept()
    if (err != nil) {
      log.Fatal(err)
    }

    stre := []byte("hello")
    n, err := conn.Read(stre)
    
    if (err != nil) {
      log.Fatal(err)
    }
  
    fmt.Printf("Read %v bytes from connection\n", n)
    fmt.Printf("Message recieved: %v\n", string(stre))


    //respond to connection
    conn.Close()
  }
}
