<script>
  import NoiseBG from "./lib/NoiseBG.svelte";
  import Nebula from "./lib/Nebula.svelte";
  import Structures from "./lib/Structures.svelte";
  import SaturationSelect from "./lib/SaturationSelect.svelte";
  import { pluginParams } from "./store.js";
  import { value } from "canvas-sketch-util/random";

  // print out current width and height
  let width = window.innerWidth;
  let height = window.innerHeight;

  let val;

  const onResize = () => {
    // console.log("resizing");
    width = window.innerWidth;
    height = window.innerHeight;
  };

  // Interop bindings
  function requestParamValueUpdate(paramId, value) {
    console.log(paramId, value);
    if (typeof globalThis.__postNativeMessage__ === "function") {
      globalThis.__postNativeMessage__("setParameterValue", {
        paramId,
        value,
      });
    }
  }
</script>

<svelte:window on:resize={() => onResize()} />

<main>
  <!-- <NoiseBG /> -->
  <Structures />
  <Nebula />
  <h1>Crann Bethadh</h1>
  <SaturationSelect />
  <!-- <p class="subtitle">
    Warm Fuzz through Veiled Glass and Nebula
  </p> -->

  <div class="sliders">
    <h3>
      {"Drive: " + ($pluginParams.drive * 100).toFixed(0) + "%"}
    </h3>
    <div class="range">
      <div class="slidecontainer">
        <input
          type="range"
          min="0"
          max="1"
          step="0.01"
          bind:value={$pluginParams.drive}
          class="slider"
          id="myRange"
          on:input={(e) => {
            requestParamValueUpdate("drive", parseFloat(e.srcElement.value));
          }}
        />
      </div>
    </div>

    <h3>
      {"Convolution: " + ($pluginParams.convolution * 100).toFixed(0) + "%"}
    </h3>
    <div class="range">
      <div class="slidecontainer">
        <input
          type="range"
          min="0"
          max="1"
          step="0.01"
          bind:value={$pluginParams.convolution}
          class="slider"
          id="myRange"
          on:input={(e) => {
            requestParamValueUpdate(
              "convolution",
              parseFloat(e.srcElement.value),
            );
          }}
        />
      </div>
    </div>

    <h3>
      {"Mix: " + ($pluginParams.feedback * 100).toFixed(0) + "%"}
    </h3>
    <div class="range">
      <div class="slidecontainer">
        <input
          type="range"
          min="0"
          max="1"
          step="0.01"
          bind:value={$pluginParams.feedback}
          class="slider"
          id="myRange"
          on:input={(e) => {
            requestParamValueUpdate("mix", parseFloat(e.srcElement.value));
          }}
        />
      </div>
    </div>
  </div>

  <!-- <div class="slidecontainer">
    <h3>drive</h3>
    <input type="range" min="1" max="100" value="50" class="slider" id="myRange">
  </div> -->
</main>

<style>
  @import url("https://fonts.googleapis.com/css2?family=Style+Script&display=swap");

  h1 {
    margin-left: auto;
    margin-right: auto;
    color: white;
    text-align: center;
    font-family: "Style Script", cursive;
    font-size: 5em;
    z-index: 1;
  }

  h3 {
    color: white;
    text-align: center;
    font-family: "Style Script", cursive;
    font-size: 2em;
  }

  ul {
    text-align: center;
    font-family: "Style Script", cursive;
    font-size: 2em;
  }

  .subtitle {
    /* position: relative; */
    color: #ffffff;
  }

  .slidecontainer {
    width: 100%; /* Width of the outside container */
    z-index: 10;
  }

  /* The slider itself */
  .slider {
    -webkit-appearance: none; /* Override default CSS styles */
    appearance: none;
    width: 100%; /* Full-width */
    height: 25px; /* Specified height */
    background: #d3d3d3; /* Grey background */
    outline: none; /* Remove outline */
    opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
    -webkit-transition: 0.2s; /* 0.2 seconds transition on hover */
    transition: opacity 0.2s;
    border-radius: 25px; /* Rounded corners */
  }

  /* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */
  .slider::-webkit-slider-thumb {
    -webkit-appearance: none; /* Override default look */
    appearance: none;
    width: 25px; /* Set a specific slider handle width */
    height: 25px; /* Slider handle height */
    background: #04aa6d; /* Green background */
    cursor: pointer; /* Cursor on hover */
    border-radius: 25px; /* Rounded corners */
  }

  .slider::-moz-range-thumb {
    width: 25px; /* Set a specific slider handle width */
    height: 25px; /* Slider handle height */
    background: #04aa6d; /* Green background */
    cursor: pointer; /* Cursor on hover */
  }

  input {
    z-index: 10;
  }

  .sliders {
    margin-top: 10vh;
  }
</style>
