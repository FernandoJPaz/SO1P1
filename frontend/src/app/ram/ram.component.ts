import { Component, OnInit } from '@angular/core';
import { HttpClient } from  '@angular/common/http';
import { Injectable } from  '@angular/core';

@Component({
  selector: 'app-ram',
  templateUrl: './ram.component.html',
  styleUrls: ['./ram.component.css']
})
export class RamComponent implements OnInit {

  private url = 'https://my-json-server.typicode.com/JSGund/XHR-Fetch-Request-JavaScript/posts';
  Reportes: any[] = [];

  constructor(public http: HttpClient) { }

  public getData() {

    this.http.get<any[]>(this.url)
    .subscribe(data => {
      console.log(data)
      this.Reportes = data
    }, error => {
      console.log(error)
    });
  }

  ngOnInit(): void {
    this.getData()
  }

}
