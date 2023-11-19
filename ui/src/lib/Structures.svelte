<script>
	import { onMount, onDestroy } from 'svelte';
     import { pluginParams } from '../store.js'
     import { createEventDispatcher } from "svelte";
     import { get } from 'svelte/store';
     import random from 'canvas-sketch-util/random'

     
     const dispatch = createEventDispatcher();
     
     let canvas;
     let scale = window.devicePixelRatio; 
     $: width = window.innerWidth;
     $: height = window.innerHeight;
     let isResizing= false;
     let print;

     let mouse = { x: 200, y: 200 };

     const structureArray = [];
     const downStructureArray = [];

     function onResize(e){
          isResizing = true;
          
          var rect = canvas.getBoundingClientRect();

          console.log(rect.left, rect.bottom);
          width = window.innerWidth;
          height = window.innerHeight;

          canvas.style.width = `${width}px`;
          canvas.style.height = `${height}px`;
          
          scale = window.devicePixelRatio; 
          console.log("scale: "+scale);
          canvas.width = Math.floor(width * scale);
          canvas.height = Math.floor(height * scale);
          
          
          setTimeout(() => {
               isResizing = false;
          }, 100)
     }

     function followMouse(e) {
          var rect = canvas.getBoundingClientRect();
          mouse.x = e.clientX - rect.left;
          mouse.y = e.clientY - rect.top;
          
          // console.log(e.clientX, e.clientY);
     }


	onMount(() => {
     
		const ctx = canvas.getContext('2d');
		let frame = requestAnimationFrame(loop);
          let time = 0;
          const r = Math.random() *.3 + .4;

          width = window.innerWidth;
          height = window.innerHeight;
        
          canvas.style.width = `${width}px`;
          canvas.style.height = `${height}px`;

          // Change to 1 on retina screens to see blurry canvas.
          canvas.width = Math.floor(width * scale);
          canvas.height = Math.floor(height * scale);

          ctx.scale(scale, scale);
          canvas.style.background = "transparent";

          let nSlow;
          let nSlow1;
          let nSlow2;
          let nFast;

          function drawFrame() {
               ctx.beginPath();

               ctx.lineWidth = 20;
               ctx.strokeStyle = "rgb(255, 255, 255)";
               ctx.strokeRect(0, 0, width, height);

          }

          class Structure {
               constructor(centerX, centerY, x, y, size) {
                    this.centerX = centerX;
                    this.centerY = centerY;
                    this.x = x;
                    this.y = y;
                    this.xVel = Math.random() * 3;
                    this.yVel = Math.random() * 2;
                    this.size = size;
                    this.ind = Math.random();
                    this.colour = 'rgba(0, 0, 0, 1)'
               } 

               draw() {
                    ctx.beginPath();
                    ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
                    ctx.lineWidth = 2;

                    ctx.strokeStyle = this.colour;
                    ctx.stroke();
                    ctx.fillStyle = this.colour;
                    ctx.fill();
               }

               update(t) {
                    this.centerX = mouse.x;
                    this.centerY = mouse.y;

                    let hF = this.y / height;
                    let wF = this.x / width;

                    
                    nSlow = random.noise1D(t * this.size * .1, 70, 1);
                    nSlow1 = random.noise1D(t * this.size, .1, 11);
                    nSlow2 = random.noise1D(t * this.size, 1, 1);
                    nFast = random.noise1D(20, 77, 10);
                    
                    print = 22000 * this.size * Math.abs(Math.sin(t*.0001));
                    this.colour = `rgba(${ 200 * hF * this.ind * Math.abs(Math.sin(t * 0.001 * this.ind))}, ${ (255 * hF * this.ind * Math.abs(Math.sin(t * 0.001 * this.ind + Math.PI * 3)))}, ${ 200 * hF * this.ind * Math.abs(Math.sin(t * 0.001 * this.ind))}, ${ hF * this.ind * Math.abs(Math.sin(t * 0.01 * this.ind + Math.PI))})`;

                    this.x += Math.sin(t * 0.001*this.ind*nSlow);
                    // this.x +=  Math.sin(t * 0.01 + this.size*2);

                    this.y = this.y - 1 * this.yVel * Math.cos(0.01 * wF);

                    // this.size = (1-hF) * .013;
                    this.size -= 0.01 * Math.abs(nSlow1 * 0.01);

                    if (this.size <= 0){
                         this.size = Math.random();
                         this.y = height + this.size;
                         this.x = width * 0.1 * Math.random();
                    }

                    if (this.y > height){
                         this.size = Math.random() * .5;
                         this.y = height + 10 * this.size;
                    }

                    else if (this.y < -this.size) {
                         this.y = height // + 2 * this.size;
                         this.x = width * 0.1 * Math.random();
                         this.size = Math.random() * .2;
                    }
                    
                    if (this.x > width ){
                         this.x = -this.size ;
                         this.size = Math.random() * .6;
                    }
               }
          }

          class StructureDown {
               constructor(centerX, centerY, x, y, size) {
                    this.centerX = centerX;
                    this.centerY = centerY;
                    this.x = x;
                    this.y = y;
                    this.xVel = Math.random() * 3;
                    this.yVel = Math.random() * 2;
                    this.size = size;
                    this.ind = Math.random();
                    this.colour = 'rgba(0, 0, 0, 1)'
               } 

               draw() {
                    ctx.beginPath();
                    ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
                    ctx.lineWidth = 2;

                    ctx.strokeStyle = this.colour;
                    ctx.stroke();
                    ctx.fillStyle = this.colour;
                    ctx.fill();
               }

               update(t) {
                    this.centerX = mouse.x;
                    this.centerY = mouse.y;

                    let hF = this.y / height;
                    let wF = this.x / width;

                    
                    nSlow = random.noise1D(t * this.size * .1, 70, 1);
                    nSlow1 = random.noise1D(t * this.size, .1, 11);
                    nSlow2 = random.noise1D(t * this.size, 1, 1);
                    nFast = random.noise1D(20, 77, 10);
                    
                    this.colour = `rgba(${ (200 * (1-hF) * this.ind * Math.abs(Math.sin(t * 0.001 * this.ind)))}, ${ (255 * hF * this.ind * Math.abs(Math.sin(t * 0.001 * this.ind + Math.PI * 3)))}, ${ 200 * hF * this.ind * Math.abs(Math.sin(t * 0.001 * this.ind))}, ${ hF * this.ind * Math.abs(Math.sin(t * 0.01 * this.ind + Math.PI))})`;

                    this.x += Math.sin(t * 0.001*this.ind*nSlow);
                    // this.x +=  Math.sin(t * 0.01 + this.size*2);

                    this.y = this.y - 1 * this.yVel * Math.cos(0.01 * wF);

                    // this.size = (1-hF) * .013;
                    this.size -= 0.01 * Math.abs(nSlow1 * 0.01);

                    if (this.size <= 0){
                         this.size = Math.random();
                         this.y = height;
                         this.x = width * 0.9 + width * 0.1 * Math.random();
                    }

                    if (this.y > height){
                         this.size = Math.random() * .5;
                         this.y = height;
                    }

                    // else if (this.y < -this.size) {
                    //      this.y = height // + 2 * this.size;
                    //      this.x = width * 0.9 + width * 0.1 * Math.random();
                    //      this.size = Math.random() * .2;
                    // }
                    
                    if (this.x > width ){
                         width * 0.9 + width * 0.1 * Math.random();
                         this.size = Math.random() * .6;
                    }
               }
          }
         
          function initStructures(numStructs) {
               for (let i = 0; i < numStructs; i++) {
                    structureArray.push( new Structure(
                         mouse.x,
                         mouse.y,
                         width * 0.1 * Math.random(), 
                         height * Math.random(),
                         Math.random() * .5
                    ) );
               }

               for (let i = 0; i < numStructs; i++) {
                    downStructureArray.push( new StructureDown(
                         mouse.x,
                         mouse.y,
                         width * 0.9 + width * 0.1 * Math.random(), 
                         height * Math.random(),
                         Math.random() * .5
                    ) );
               }
          }

          function drawStructures(t) {
               for (let i = 0; i < structureArray.length; i++) {
                    structureArray[i].draw();
                    structureArray[i].update(t);

                    downStructureArray[i].draw();
                    downStructureArray[i].update(t);
               }
          }

          initStructures(500);

		function loop(t) {

               ctx.clearRect(0, 0, width, height);
               requestAnimationFrame(loop);
              
               time = t;

               if(isResizing)  {
                    ctx.scale(scale, scale);
               }

               drawStructures(t);
               drawFrame();

			return () => {	
				cancelAnimationFrame(frame);
			}
		}
	});

</script>

<svelte:window  
     on:mousemove={(e) => { followMouse(e)} }
     on:resize={(e) => onResize(e)}
/>


<div class="container">
     <!-- <h1>{print}</h1> -->
     <canvas 
            bind:this={canvas}
       ></canvas>
  </div>

<style>
 
	canvas { 
          width: 100vw;
          height: 100vw;
          /* margin-left: auto;
          margin-right: auto; */
          position: fixed;
          top: 0;
          left: 0;
          /* aspect-ratio: 1; */
          /* pointer-events: none; */
          /* user-select: none; */
          z-index: 0;
          filter: blur(10px) contrast(0.2) luminosity(10.2);
	}
	
</style>