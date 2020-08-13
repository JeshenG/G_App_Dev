import React, { useEffect, useState } from 'react'
import { useParams } from 'react-router-dom'
import axios from 'axios'
import Loader from '../Components/Loader'
import ProductCard from '../Components/ProductCard'
import { useAxiosGet } from '../Hooks/HttpRequests'


function Home() {
    const url = `https://5f258cdec85de20016293214.mockapi.io/products?page=2&limit=10`; 
    let products = useAxiosGet(url); 
    let content = null
    
    if(products.error){
        content = <p>There was an error please refresh or try again later</p>
    }

    if (products.loading) {
        content = <Loader></Loader>
    }

    if (products.data) {
        //treated like an array 
        content =
           products.data.map((product) => 
           <div key={product.id}>
               <ProductCard product={product}/>
           </div>)
    }

    return (
        <div>
            <h1 className="font-bold text-2xl">Best Sellers</h1>
            {content}
        </div>
    )
}

export default Home;