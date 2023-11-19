<script>

	import { onMount, onDestroy } from 'svelte';
     import { pluginParams } from './../store.js'
     import { createEventDispatcher } from "svelte";
     import { get } from 'svelte/store';

     
     const dispatch = createEventDispatcher();
     
     let canvas;
     let scale = window.devicePixelRatio; 
     let width = window.innerWidth;
     let height = window.innerHeight;
     let isResizing= false;

     let bgNoise = 0.4;
     function onResize(){
          isResizing = true; 
          console.log(isResizing);

          width = window.innerWidth;
          height = window.innerHeight;
          canvas.style.width = `${width}px`;
          canvas.style.height = `${height}px`;
          
          canvas.width = Math.floor(width * scale);
          canvas.height = Math.floor(height * scale);
          
          setTimeout(() => {
               isResizing = false;
          }, 100)
     }



	onMount(() => {
     
		const ctx = canvas.getContext('2d');
		let frame = requestAnimationFrame(loop);
          let time = 0;
          const r = Math.random() *.3 + .4;
          // ctx.filter = "url(./filter.svg#turb)";
          // const scale = window.devicePixelRatio; 

          width = window.innerWidth;
          height = window.innerHeight;
        
          canvas.style.width = `${width}px`;
          canvas.style.height = `${height}px`;

          // Change to 1 on retina screens to see blurry canvas.
          canvas.width = Math.floor(width * scale);
          canvas.height = Math.floor(height * scale);

          ctx.scale(scale, scale);
          canvas.style.background = "transparent";

          function noise(ctx) {
               const w = canvas.width,
                              h = canvas.height,
                              iData = ctx.createImageData(w, h),
                              buffer32 = new Uint32Array(iData.data.buffer),
                              len = buffer32.length
                    let i = 0

               for(; i < len;i++)
                    
                    if (Math.random() < 0.5) buffer32[i] = 0xff121212;

                    ctx.putImageData(iData, 0, 0);
          }
          noise(ctx);

		function loop(t) {

               requestAnimationFrame(loop);
              
               time = t;

               if(isResizing)  {
                    noise(ctx);
                    ctx.scale(scale, scale);
               }

			return () => {	
				cancelAnimationFrame(frame);
			}
		}
	});

</script>

<svelte:window 
     
    on:resize={onResize}

  />


<canvas 
     style="--noise-amount: {bgNoise}"
	bind:this={canvas}
    
    
></canvas>

<style>

	canvas { 
          width: 100vw;
          height: 100vw;
          /* margin-left: auto;
          margin-right: auto; */
          position: fixed;
          top: 0;
          left: 0;
          opacity: var(--noise-amount);
          aspect-ratio: 1;
          pointer-events: none;
          user-select: none;
          z-index: 10;
	}
	
</style>