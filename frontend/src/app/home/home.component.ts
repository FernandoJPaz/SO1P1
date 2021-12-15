import { Component, OnInit } from '@angular/core';
import { HttpClient } from  '@angular/common/http';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  private url = 'http://127.0.0.1:3000/ram';
  object: any;
  ram: any[] = [];
  ram_free: any[] = [];
  ram_percent: any[] = [];
  ram_usage: any[] = [];

  constructor(public http: HttpClient) { }

  public getData() {

    this.http.get<any[]>(this.url)
    .subscribe(data => {

      this.object = data
      this.ram = this.object['ram']
      this.ram_free = this.object['ram_free']
      this.ram_percent = this.object['ram_percent']
      this.ram_usage = this.object['ram_usage']

      console.log(this.object)

    }, error => {
      console.log(error)
    });
  }

  ngOnInit(): void {
    this.getData()
  }

}
