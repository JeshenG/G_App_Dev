import React, { useState, useEffect } from 'react'
import axios from 'axios'
import { useParams } from 'react-router-dom'
import Loader from '../Components/Loader'
import { useAxiosGet } from '../Hooks/HttpRequests';

//use axios to send though http request 

function Product() {
    const { id } = useParams();
    //need to setup API first, using Mock API
    const url = `https://5f258cdec85de20016293214.mockapi.io/products/${id}`;
    let content = null;
    let product = useAxiosGet(url); 

    if(product.error){
        content = <p>There was an error please refresh or try again later</p>
    }

    if (product.loading) {
        content = <Loader> </Loader>
    }

    //only display product if there is data 
    if (product.data) {
        content =
            <div>
                <h1 className="text-2xl font-bold mb-3">
                    {product.data.name}
                </h1>
                <div>
                    <img src={product.data.images[0].imageUrl} alt={product.data.name} />
                </div>
                <div className="font-bold text-xl mb-3">
                    R {product.data.price}
                </div>
                <div>
                    {product.data.description}
                </div>
            </div>
    }

    return (
        <div>
            {content}
        </div>
    )
}

export default Product;