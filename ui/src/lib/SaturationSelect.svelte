<script>
    import { onMount, createEventDispatcher } from 'svelte';
    import { pluginParams } from '../store.js'

    const dispatch = createEventDispatcher();

    let placeholder = "Select Colour!"
    let selected;

    const saturators = ["None", "Arcsinh 1", "Arcsinh 2", "Sigmoid", "hyperbolic Tangent"];
    
    onMount(() => {
      // selectedColor = $pluginParams.selectedColor;
    });

    function setConvo() { 
      $pluginParams.satType = selected;
      dispatch('change', $pluginParams.satType );
    }

    
   
</script>
        <div class="container"> 
          <select class="colorChooserA" bind:value={selected} on:change="{setConvo}">
            {#if placeholder}
              <option value="" disabled selected>{placeholder}</option>
            {/if}
                {#each saturators as sat }
                  <option value={sat}>{sat}</option>
                {/each}     
          </select>
      </div>
<style>
 
   
 .container  {
   
   /* display: flex;
   justify-content: center;
   flex-direction: row;
   position: fixed;
   top: 83vh;
   left: 36.5vw; */
   background-color: transparent;
   /* padding: 0rem;
   height: 20vh;
   width: 30vw; */
   z-index: 10;
 }

 .colorChooserA {
  -webkit-appearance: none;
     appearance: none;
     /* min-width: 20vw;
     min-height: 3vh; */
     border-radius: 10px;
     border-color: white;
     /* margin: auto; */
     font-family: "Avenir Next Condensed";
     padding: .2rem 3rem;
     background: rgba(58, 58, 58, 0.01);
     backdrop-filter: blur(5px);
     -webkit-backdrop-filter: blur(5px);
     color: white;
     font-weight: normal;
     font-size: .8rem;
     text-align-last: center;
     z-index: 4;

 }

 *:focus {
  outline: 0;
}

</style>