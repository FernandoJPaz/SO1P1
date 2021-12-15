import { Component, OnInit } from '@angular/core';
import { HttpClient } from  '@angular/common/http';
import { Injectable } from  '@angular/core';

@Component({
  selector: 'app-ram',
  templateUrl: './ram.component.html',
  styleUrls: ['./ram.component.css']
})
export class RamComponent implements OnInit {

  private url = 'http://127.0.0.1:3000/cpu';
  Reportes: any[] = [];
  Process: any[] = [];
  Process_Total: any[] = [];

  usersx: any;
  contacts:any[]=[];

  object: any;
  process:any;
  objecthijo: any;

  constructor(public http: HttpClient) { }

  public getData() {

    this.http.get<any[]>(this.url)
    .subscribe(data => {

      /*
      this.usersx = data;
      this.contacts = this.usersx['process']
      console.log(this.contacts)
       */

      this.object = data
      this.process = this.object['process']
      this.Process_Total = this.object['process_total']

      this.objecthijo = this.process['Object']
      

      console.log(this.process)

    }, error => {
      console.log(error)
    });
  }

  ngOnInit(): void {
    this.getData()
  }

}
