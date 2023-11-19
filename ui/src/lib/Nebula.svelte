<script>
     import { onMount } from "svelte";
     import { pluginParams } from "./../store.js";
     import { createEventDispatcher } from "svelte";
     import { get } from "svelte/store";
     import random from "canvas-sketch-util/random";

     const dispatch = createEventDispatcher();

     let innerWidth = window.innerWidth;
     let innerHeight = window.innerHeight;

     let canvas;

     let maxLevel;
     let branches;
     let sides;
     let mysteryCounter = 0;

     function mysteryCount() {
          mysteryCounter++;

          if (mysteryCounter > 10) {
               // alert("we're there!");
               $pluginParams.mystery = true;

               setTimeout(() => {
                    $pluginParams.mystery = false;
                    mysteryCounter = 0;
               }, 2000);
          } else $pluginParams.mystery = false;
     }

     onMount(() => {
          const ctx = canvas.getContext("2d");
          let frame = requestAnimationFrame(loop);
          let time = 0;
          // ctx.filter = "url(./filter.svg#turb)";

          const scale = window.devicePixelRatio;

          let width = window.innerWidth;
          let height = window.innerHeight;
          canvas.style.width = `${width}px`;
          canvas.style.height = `${height}px`;

          // Change to 1 on retina screens to see blurry canvas.
          canvas.width = Math.floor(width * scale);
          canvas.height = Math.floor(height * scale);

          ctx.scale(scale, scale);
          canvas.style.background = "transparent";

          maxLevel = Math.floor(Math.random() * 4 + 2);
          branches = Math.floor(Math.random() + 1);
          sides = Math.floor(Math.random() * 5 + 4);
          const spread = Math.random() * 0.48 + 0.51;
          let lineWidth = Math.floor(Math.random() * 7 + 1);
          let grow = 0.0001;
          let distance = 1;
          let branchOut = 0.01;
          let scaler = .5;
          const MAX_CIRCLE = 2;
          const rotation = Math.random() * 0.01 + 0.01;

          const NUM_OF_STARS = 3;
          ctx.translate(canvas.width / 4, canvas.height / 4);

          const angle = Math.PI * 2 * spread;
          // ctx.globalCompositeOperation = 'lighter';

          let nSlow = random.noise2D(time * 0.5, distance, 0.0002);
          // let nFast = random.noise2D(time, distance, 0.0003);

          function drawLine(level) {
               if (level > maxLevel) return;

               ctx.beginPath();
               ctx.fillStyle = "rgba(255, 255, 255, " + 0.001 + ")";
               ctx.arc(0, 0, distance * lineWidth * 25, 0, Math.PI * 2);
               ctx.arc(
                    sides * 200 * 0.5 * scaler,
                    0,
                    distance * lineWidth * 10,
                    0,
                    Math.PI * 2
               );
               ctx.fill();
               ctx.closePath();

               for (let i = 1; i < 7; i++) {
                    ctx.beginPath();
                    ctx.fillStyle =
                         "rgba(" +
                         Math.floor(255 / 7) * i +
                         ", " +
                         Math.floor(255 / 7) * i +
                         ", " +
                         Math.floor(255 / 7) * i +
                         ", " +
                         0.5 * 0.07 +
                         ")";
                    ctx.arc(
                         30 + 0.5 * i * 40,
                         70 + 0.5 * i * 40,
                         40 +
                              0.5 *
                                   Math.abs(nSlow) *
                                   700 *
                                   i *
                                   0.03,
                         0,
                         Math.PI * 2
                    );
                    ctx.arc(
                         10 + 0.5 * i * 20,
                         30 + 0.5 * i * 20,
                         20 +
                              0.5 *
                                   Math.abs(nSlow) *
                                   500 *
                                   i *
                                   0.03,
                         0,
                         Math.PI * 2
                    );
                    ctx.fill();
                    ctx.closePath();

                    ctx.rotate(Math.PI * distance * 0.000007);
               }

               for (let i = 1; i < branches + 1; i++) {
                    ctx.save();
                    ctx.translate(
                         (0.5 * scaler * 1000 * i) /
                              (branches + 1),
                         0
                    );
                    ctx.scale(0.5, 0.5);
                    ctx.save();

                    ctx.rotate(angle);
                    drawLine(level + 1);
                    ctx.restore();
                    ctx.save();

                    ctx.rotate(-angle);
                    drawLine(level + 1);
                    ctx.restore();
                    ctx.restore();
               }
          }

          function loop(t) {
               ctx.clearRect(
                    -canvas.width,
                    -canvas.height,
                    canvas.width * 2,
                    canvas.height * 2
               );

               nSlow = random.noise2D(time * 0.5, distance, 0.0004);
               // nFast = random.noise2D(time, distance, 0.0003);
               requestAnimationFrame(loop);

               time = t;

               for (let i = 0; i < sides; i++) {
                    drawLine(0);
                    ctx.rotate((Math.PI * 2) / sides);
               }

               ctx.rotate(((Math.PI * 2) / 30000) * rotation);

               distance += branchOut;

               if (distance > MAX_CIRCLE || distance <= 100) {
                    branchOut *= -1;
               }

               return () => {
                    cancelAnimationFrame(frame);
               };
          }
     });
</script>

<svelte:window bind:innerWidth bind:innerHeight />

<!-- <h3>{mysteryCounter}</h3>
<h3 style="left: 20vw">{$pluginParams.mystery}</h3> -->
<canvas bind:this={canvas} on:mouseenter={mysteryCount} />

<style>
     h3 {
          position: fixed;
          top: 20vh;
          left: 20vw;
          color: white;
     }
     canvas {
          width: 100vw;
          height: 100vh;
          margin-left: auto;
          margin-right: auto;
          position: fixed;
          top: 0vh;
          left: 0vw;
          /* background: black; */
          /* filter: contrast(10); */
          /* filter: drop-shadow(0px 0px 40px rgb(255, 146, 4)); */
          /* backdrop-filter: blur(23px); */
          /* filter: drop-shadow(0px 0px 30px rgb(255, 146, 4)); */
          filter: drop-shadow(0px 0px 40px rgb(255, 75, 4));
          filter: drop-shadow(0px 0px 70px rgb(255, 146, 4)); 
          filter: drop-shadow(0px 0px 120px rgb(255, 146, 4));
          filter: hue-rotate(20deg);
          /* background: rgba(58, 58, 58, 0.01); */
          filter: blur(10px);
          background-blend-mode: luminosity;
          z-index: 0;
     }
</style>
